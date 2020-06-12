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
#include <iostream>


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
    bool run;

    unsigned int startX;
    unsigned int startY;
    unsigned int stopX;
    unsigned int stopY;
    unsigned long aliveCells;
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
    cellType maxAge;
    unsigned int mapWidth;
    unsigned int mapHeight;

    unsigned long alive;
    unsigned long frame;
    unsigned long durationStep;

    cellType** map;
    cellType** newMap;

    int historySize;
    bool historyEnabled = true;
    std::vector <HistoryItem*> history;

    Life();
    explicit Life(int threadsCount);
    Life(int width, int height, int threadsCount=0);
    ~Life();

    void clearHistory(int start=0, int end=-1);

    void resizeMap(unsigned int width, unsigned int height);
    void newGame(bool empty=false);
    void generateMap(bool empty=false) const;

    cellType** copyMap(cellType** sourceMap) const;
    void copyMap(cellType** sourceMap, cellType** targetMap) const;

    void normalize(int& x, int& y) const;
    cellType getCell(int x, int y) const;
    void setCell(int x, int y, cellType v=1) const;

    unsigned char getSumMur(unsigned int x, unsigned int y) const;
    unsigned char getSumMurFast(unsigned int x, unsigned int y) const;
    cellType handleCell(unsigned int x, unsigned int y) const;
    cellType handleCellFast(unsigned int x, unsigned int y) const;
    void save();
    void step();
    void back();

    int threadsCount;

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
