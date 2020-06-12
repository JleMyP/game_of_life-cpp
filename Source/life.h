#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

#define THREADS_ENABLED

// wtf
// TODO
/*
    cuda
    ������������ �������������� ������
    �������������� ���� ��� ������ �������
    ����������� �����
    ��� ���������� ������� ����� - ���������� ��, � �� ����������������
    �������� ��������� ������� � ��
*/


#include <cstdlib>
#include <chrono>
#include <vector>

#ifdef THREADS_ENABLED
#include <thread>
#include <mutex>
#include <condition_variable>
#endif

/*
#ifndef NDEBUG
srand(666);
#endif
*/

#define clock_now std::chrono::high_resolution_clock::now
#define clock_cast_microsec(arg) std::chrono::duration_cast<std::chrono::microseconds>(arg).count()

#define ALIVE 1
#define DEAD 0

typedef unsigned char cellType;


void removeMap(cellType** map, unsigned int width);


struct ThreadConfig {
    bool alive = true;
    bool run = false;

    unsigned int startX = 0;
    unsigned int startY = 0;
    unsigned int stopX = 0;
    unsigned int stopY = 0;
    unsigned long aliveCells = 0;
    // TODO: thread pointer
};


struct HistoryItem {
    unsigned long alive;
    unsigned int width;
    cellType** map;

    HistoryItem(unsigned int alive, unsigned int width, cellType** map) : width(width), alive(alive), map(map) { }
    ~HistoryItem() {
        removeMap(map, width);
    }
};


class Life {
public:
    cellType maxAge = 20;
    int mapWidth;
    int mapHeight;

    unsigned long alive = 0;
    unsigned long frame = 0;
    unsigned long durationStep = 0;

    cellType** map = nullptr;
    cellType** newMap = nullptr;

    int historySize = 1000;
    bool historyEnabled = true;
    int threadsCount;

    Life();
    explicit Life(int threadsCount);
    Life(int width, int height, int threadsCount=0);
    ~Life();

    cellType getCell(int x, int y) const;
    void setCell(int x, int y, cellType v=1) const;

    unsigned int getUsedHistorySize();
    unsigned int getMaxHistorySize();
    void historyReserve(unsigned int size);
    void clearHistory(int start=0, int end=-1);
    void resizeMap(unsigned int width, unsigned int height);
    void newGame(bool empty=false);
    void save();
    void step();
    void back();

private:
    std::vector <HistoryItem*> history;

    void generateMap(bool empty=false) const;
    cellType** copyMap(cellType** sourceMap) const;
    void copyMap(cellType** sourceMap, cellType** targetMap) const;

    void normalize(int& x, int& y) const;

    unsigned char getSumMur(int x, int y) const;
    unsigned char getSumMurFast(int x, int y) const;
    cellType handleCell(int x, int y) const;
    cellType handleCellFast(int x, int y) const;

#ifdef THREADS_ENABLED
    std::mutex waitLock;
    std::condition_variable threadsStart;
    std::condition_variable threadsFinish;

    std::vector<ThreadConfig*> configs;
    std::vector<std::thread*> threads;

    void partStep(ThreadConfig& config);
    void waitThreads();
#endif
};

#endif
