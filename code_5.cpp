// 求解迷宫最短路径
// Created by yan on 2021/4/25.
// 链表，队列，BFS(广度优先搜索)

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory.h>

using namespace std;

// 迷宫大小
const int mazeHeight = 20;
const int mazeWidth = 40;

// 迷宫生成器参数 取值[0.0, 1.0]
const double probability = .12;           // 这个参数影响障碍物数量
const double conProbability = .48;        // 这个参数影响障碍物的长度
const double groupProbability = .03;      // 这个参数影响障碍物的面积

// 坐标结构体
typedef struct Position {
    int x;
    int y;
} Position;

Position startPoint({0, mazeHeight / 2});             // 设置起点
Position endPoint({mazeWidth - 1, mazeHeight / 2});   // 设置终点

// 链表节点
typedef Position ElemType, *PElemType;
typedef struct LNode {
    ElemType data;
    LNode *next;
} LNode, *PLNode;

// 队列结构体
typedef unsigned long long SizeType;
typedef struct Queue {
    PLNode qFront;                   // 头节点，不含数据，next 为队首
    PLNode qBack;                    // 尾节点，含数据，本身即为队尾
    SizeType qSize;                  // 队列大小（长度）

    void init();                     // 初始化

    bool empty() const;              // 判断队空

    SizeType size() const;           // 获取队列大小

    void push(const ElemType &x);    // 入队

    void pop();                      // 出队

    ElemType front() const;          // 获取队首

    ElemType back() const;           // 获取队尾

    void destroy();                  // 销毁
} Queue;

void Queue::init() {
    qFront = new LNode();
    qFront->next = nullptr;
    qBack = qFront;
    qSize = 0;
}

bool Queue::empty() const {
    return qFront == qBack;
}

SizeType Queue::size() const {
    return qSize;
}

void Queue::push(const ElemType &x) {
    auto pLNode = new LNode();
    pLNode->data = x;
    pLNode->next = nullptr;
    qBack->next = pLNode;
    qBack = qBack->next;
    ++qSize;
}

void Queue::pop() {
    if (empty()) return;
    PLNode delNode = qFront;
    qFront = qFront->next;
    delete delNode;
    --qSize;
}

ElemType Queue::front() const {
    return qFront->next->data;
}

ElemType Queue::back() const {
    return qBack->data;
}

void Queue::destroy() {
    while (not empty()) {
        pop();
    }
    delete qFront;
    qFront = nullptr;
    qBack = nullptr;
    qSize = 0;
}

int maze[mazeHeight][mazeWidth] = {};  // 迷宫矩阵
int dist[mazeHeight][mazeWidth] = {};  // 每个点到入口的最短距离, -1为无法到达
int path[mazeHeight][mazeWidth] = {};  // 最短的路

void clearMaze() {
    memset(maze, 0, mazeHeight * mazeWidth * sizeof(int));
}

void clearDist() {
    memset(dist, -1, mazeHeight * mazeWidth * sizeof(int));
}

void clearPath() {
    memset(path, 0, mazeHeight * mazeWidth * sizeof(int));
}

// 迷宫生成器
void generate() {
    for (int i = 0; i < mazeHeight; ++i) {
        for (int j = 0; j < mazeWidth; ++j) {
            if (i == 0 or j == 0 or i == mazeHeight - 1 or j == mazeWidth - 1) {
                maze[i][j] = 1;
            } else {
                double tempProb = probability;
                if (i > 1 and j > 1 and (maze[i - 1][j] or maze[i][j - 1])) {
                    if (maze[i - 1][j] and maze[i][j - 1] and maze[i - 1][j - 1]) {
                        tempProb = groupProbability;
                    } else {
                        tempProb = conProbability;
                    }
                }
                if (rand() > RAND_MAX * (1 - tempProb)) {
                    maze[i][j] = 1;
                } else {
                    maze[i][j] = 0;
                }
            }
        }
    }
    maze[startPoint.y][startPoint.x] = maze[endPoint.y][endPoint.x] = 0;
}

// 打印迷宫
void printMaze() {
    for (auto &i : maze) {
        for (int j : i) {
            cout << (j ? '#' : ' ');
        }
        cout << endl;
    }
}

void printSolution() {
    for (int i = 0; i < mazeHeight; ++i) {
        for (int j = 0; j < mazeWidth; ++j) {
            if (path[i][j]) {
                cout << '+';
            } else {
                cout << (maze[i][j] ? '#' : ' ');
            }
        }
        cout << endl;
    }
}

// 求解
void solve() {
    Queue queue;
    queue.init();
    clearDist();
    dist[startPoint.y][startPoint.x] = 0;  // 起点到起点的距离为0
    queue.push(startPoint);                // 起点入队

    while (not queue.empty()) {
        // 取出队首
        Position currentPoint = queue.front();
        queue.pop();
        // 将上、下、左、右点依次入队
        if (currentPoint.x - 1 >= 0 and maze[currentPoint.y][currentPoint.x - 1] == 0
            and dist[currentPoint.y][currentPoint.x - 1] == -1) {
            dist[currentPoint.y][currentPoint.x - 1] = dist[currentPoint.y][currentPoint.x] + 1;
            queue.push({currentPoint.x - 1, currentPoint.y});
        }
        if (currentPoint.y - 1 >= 0 and maze[currentPoint.y - 1][currentPoint.x] == 0
            and dist[currentPoint.y - 1][currentPoint.x] == -1) {
            dist[currentPoint.y - 1][currentPoint.x] = dist[currentPoint.y][currentPoint.x] + 1;
            queue.push({currentPoint.x, currentPoint.y - 1});
        }
        if (currentPoint.x + 1 < mazeWidth and maze[currentPoint.y][currentPoint.x + 1] == 0
            and dist[currentPoint.y][currentPoint.x + 1] == -1) {
            dist[currentPoint.y][currentPoint.x + 1] = dist[currentPoint.y][currentPoint.x] + 1;
            queue.push({currentPoint.x + 1, currentPoint.y});
        }
        if (currentPoint.y + 1 < mazeWidth and maze[currentPoint.y + 1][currentPoint.x] == 0
            and dist[currentPoint.y + 1][currentPoint.x] == -1) {
            dist[currentPoint.y + 1][currentPoint.x] = dist[currentPoint.y][currentPoint.x] + 1;
            queue.push({currentPoint.x, currentPoint.y + 1});
        }
    }
    queue.pop();
}

// 回溯，根据距离矩阵计算路径
void backtrack() {
    // 从终点开始
    Position currentPoint = endPoint;
    path[currentPoint.y][currentPoint.x] = 1;
    while (true) {
        // 如果到达某一点的距离比相邻点多一，则说明可由该点到相邻点
        // 依次判断上、下、左、右点
        if (dist[currentPoint.y][currentPoint.x] == dist[currentPoint.y - 1][currentPoint.x] + 1 and
            dist[currentPoint.y - 1][currentPoint.x] != -1) {
            path[currentPoint.y - 1][currentPoint.x] = 1;
            --currentPoint.y;
        } else if (dist[currentPoint.y][currentPoint.x] == dist[currentPoint.y][currentPoint.x - 1] + 1 and
                   dist[currentPoint.y][currentPoint.x - 1] != -1) {
            path[currentPoint.y][currentPoint.x - 1] = 1;
            --currentPoint.x;
        } else if (dist[currentPoint.y][currentPoint.x] == dist[currentPoint.y + 1][currentPoint.x] + 1 and
                   dist[currentPoint.y + 1][currentPoint.x] != -1) {
            path[currentPoint.y + 1][currentPoint.x] = 1;
            ++currentPoint.y;
        } else if (dist[currentPoint.y][currentPoint.x] == dist[currentPoint.y][currentPoint.x + 1] + 1 and
                   dist[currentPoint.y][currentPoint.x + 1] != -1) {
            path[currentPoint.y][currentPoint.x + 1] = 1;
            ++currentPoint.x;
        } else {
            break;
        }
    }
}

int main() {
    // 设置随机数种子
    srand((unsigned) time(nullptr));
    generate();
    cout << "迷宫: " << endl;
    printMaze();
    cout << endl;
    solve();
    cout << "答案: " << endl;
    // 如果dist数组中终点为-1，则说明无法到达终点。
    if (dist[endPoint.y][endPoint.x] == -1) {
        cout << "无法到达." << endl;
    } else {
        backtrack();
        printSolution();
        cout << "距离: " << dist[endPoint.y][endPoint.x] << endl;
    }
    return 0;
}