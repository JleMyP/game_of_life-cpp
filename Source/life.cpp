#include "life.h"


void removeMap(cellType** map, int width) {
    if (map != nullptr) {
        for (int x = 0; x < width; x++)
            delete[] map[x];
        delete[] map;
    }
}


Life::Life(): historySize(1000), history(historySize), maxAge(20) { }
Life::Life(int threadsCount): Life() {
    map = nullptr;
    newMap = nullptr;

#ifdef THREADS_ENABLED
    this->threadsCount = threadsCount;
    auto thread_func = [&](ThreadConfig& config) { partStep(config); };

    for (int i = 0; i < threadsCount; i++) {
        ThreadConfig* tc = new ThreadConfig();
        configs.push_back(tc);
        threads.push_back(new std::thread(thread_func, std::ref(*tc)));
    }
#endif
}

Life::Life(int width, int height, int threadsCount): Life(threadsCount) {
    resizeMap(width, height);
    newGame();
}


Life::~Life() {
    clearHistory();
    removeMap(map, mapWidth);
    removeMap(newMap, mapWidth);

#ifdef THREADS_ENABLED
    for (auto config : configs)
        config->alive = false;
    threadsStart.notify_all();
    waitThreads();

    for (auto thread : threads) {
        thread->join();
        delete thread;
    }

    for (auto config : configs)
        delete config;

    threads.clear();
    configs.clear();
#endif
}


void Life::clearHistory(int start, int end) {
    if (end == -1)
        end = history.size();
    if (!historyEnabled)
        return;

    for (int h = start; h < end; h++)
        delete history[h];

    history.erase(history.begin() + start, history.begin() + end);
}


void Life::resizeMap(int width, int height) {
    if (mapWidth) {
        clearHistory();
        removeMap(map, mapWidth);
        removeMap(newMap, mapWidth);
    }

    mapWidth = width;
    mapHeight = height;

    map = new cellType*[width];
    newMap = new cellType*[width];

    for (int x = 0; x < width; x++) {
        map[x] = new cellType[height];
        newMap[x] = new cellType[height];
    }

#ifdef THREADS_ENABLED
    int linesPerThread = height / threadsCount;
    for (int threadNum = 0; threadNum < threadsCount; threadNum++) {
        if (threadNum != threadsCount - 1) {
            configs[threadNum]->startY = threadNum * linesPerThread;
            configs[threadNum]->stopX = width;
            configs[threadNum]->stopY = (threadNum + 1) * linesPerThread;
            std::cout << threadNum << ": " << threadNum * linesPerThread << " - " << (threadNum + 1) * linesPerThread << std::endl;
        } else {
            configs[threadNum]->startY = threadNum * linesPerThread;
            configs[threadNum]->stopX = width;
            configs[threadNum]->stopY = (threadNum + 1) * linesPerThread + height % threadsCount;
        }
    }
#endif
}


void Life::newGame(bool empty) {
    alive = 0;
    frame = 0;

    clearHistory();
    generateMap(empty);
}


void Life::generateMap(bool empty) {
    for (int x = 0; x < mapWidth; x++) {
        for (int y = 0; y < mapHeight; y++) {
            map[x][y] = empty ? 0 : rand() % 2;
        }
    }
}


void Life::normalize(int& x, int& y) {
    if (x >= mapWidth)
        x -= mapWidth;
    else if (x < 0)
        x += mapWidth;

    if (y >= mapHeight)
        y -= mapHeight;
    else if (y < 0)
        y += mapHeight;
}


cellType Life::getCell(int x, int y) {
    normalize(x, y);
    return map[x][y] ? 1 : 0;
}


void Life::setCell(int x, int y, cellType v) {
    normalize(x, y);
    map[x][y] = v;
}


inline char Life::getSumMur(int x, int y) {
    char sum = 0;

    for (int xx = x - 1; xx < x + 2; xx++) {
        for (int yy = y - 1; yy < y + 2; yy++) {
            sum += getCell(xx, yy);
        }
    }

    return sum - (map[x][y] ? 1 : 0);
}

inline char Life::getSumMurFast(int x, int y) {
    char sum = 0;

    for (int xx = x - 1; xx < x + 2; xx++) {
        for (int yy = y - 1; yy < y + 2; yy++) {
            sum += map[xx][yy] ? 1 : 0;
        }
    }

    return sum - (map[x][y] ? 1 : 0);
}


inline cellType Life::handleCell(int x, int y) {
    cellType cell = map[x][y];
    char sum = getSumMur(x, y);
    //calculate = (sum == 3 || cell && sum == 2) ? 1 : 0;
    cellType calculate = (sum == 3 || cell && sum == 2) ? (cell < maxAge ? cell + 1 : maxAge) : DEAD;
    newMap[x][y] = calculate;
    return calculate;
}

inline cellType Life::handleCellFast(int x, int y) {
    cellType cell = map[x][y];
    char sum = getSumMurFast(x, y);
    //calculate = (sum == 3 || cell && sum == 2) ? 1 : 0;
    cellType calculate = (sum == 3 || cell && sum == 2) ? (cell < maxAge ? cell + 1 : maxAge) : DEAD;
    newMap[x][y] = calculate;
    return calculate;
}


#ifdef THREADS_ENABLED

void Life::partStep(ThreadConfig& config) {
    int startX;
    int startY;
    int stopX;
    int stopY;

    int x, y;
    long aliveCells;
    std::mutex m;

    while (42) {
        std::unique_lock<std::mutex> lock(m);
        threadsStart.wait(lock, [&]() { return config.run || !config.alive; });

        if (!config.alive)
            break;

        startX = config.startX;
        startY = config.startY;
        stopX = config.stopX;
        stopY = config.stopY;
        aliveCells = 0;

        for (x = startX + 1; x < stopX - 1; x++) {
            for (y = startY + 1; y < stopY - 1; y++) {
                if (handleCellFast(x, y))
                    aliveCells++;
            }
        }

        for (x = startX + 1; x < stopX - 1; x++) {
            if (handleCell(x, startY))
                aliveCells++;
            if (handleCell(x, stopY - 1))
                aliveCells++;
        }

        for (y = startY; y < stopY; y++) {
            if (handleCell(startX, y))
                aliveCells++;
            if (handleCell(stopX - 1, y))
                aliveCells++;
        }

        config.aliveCells = aliveCells;
        config.run = false;
        threadsFinish.notify_all();
    }
}


void Life::step() {
    auto t = clock_now();

    if (historyEnabled)
        save();

    for (auto config : configs)
        config->run = true;
    threadsStart.notify_all();
    waitThreads();

    alive = 0;
    for (auto config : configs)
        alive += config->aliveCells;

    cellType** tmp = newMap;
    newMap = map;
    map = tmp;

    frame++;
    durationStep = clock_cast_microsec(clock_now() - t);
}


inline void Life::waitThreads() {
    std::unique_lock<std::mutex> lock(waitLock);
    bool res;

    do {
        res = threadsFinish.wait_for(lock, std::chrono::milliseconds(3), [&]() {
            for (auto config : configs) {
                if (config->run)
                    return false;
            }

            return true;
        });
    } while (!res);
}

#else

void Life::step() {
    alive = 0;
    auto t = clock_now();

    if (historyEnabled)
        save();

    for (int x = 1; x < mapWidth - 1; x++) {
        for (int y = 1; y < mapHeight - 1; y++) {
            if (handleCellFast(x, y))
                alive++;
        }
    }

    for (int x = 0; x < mapWidth; x++) {
        if (handleCell(x, 0))
            alive++;
        if (handleCell(x, mapHeight - 1))
            alive++;
    }

    for (int y = 0; y < mapHeight; y++) {
        if (handleCell(0, y))
            alive++;
        if (handleCell(mapWidth - 1, y))
            alive++;
    }

    cellType** tmp = newMap;
    newMap = map;
    map = tmp;

    frame++;
    durationStep = clock_cast_microsec(clock_now() - t);
}

#endif

// TODO: ���������� �� memcpy
cellType** Life::copyMap(cellType** sourceMap) {
    int x, y;
    cellType** targetMap = new cellType*[mapWidth];

    for (x = 0; x < mapWidth; x++) {
        targetMap[x] = new cellType[mapHeight];

        for (y = 0; y < mapHeight; y++) {
            targetMap[x][y] = sourceMap[x][y];
        }
    }

    return targetMap;
}

void Life::copyMap(cellType** sourceMap, cellType** targetMap) {
    int x, y;

    for (x = 0; x < mapWidth; x++) {
        for (y = 0; y < mapHeight; y++) {
            targetMap[x][y] = sourceMap[x][y];
        }
    }
}


void inline Life::save() {
    history.push_back(new HistoryItem(alive, mapWidth, copyMap(map)));
    if (history.size() > historySize)
        clearHistory(0, 1);
}


void Life::back() {
    if (!historyEnabled || history.size() == 0)
        return;

    HistoryItem* prev = history.back();
    alive = prev->alive;
    frame--;

    copyMap(prev->map, map);

    delete history[history.size() - 1];
    history.pop_back();
}
