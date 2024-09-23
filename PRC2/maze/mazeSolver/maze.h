#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>
#include <queue>
#include <utility> // for pair
#include <set>
#include <cmath>
#include <limits>

#include <QObject>
#include <QPainter>
#include <QString>

#include <QDebug>


struct Node {
    int x, y;
    float cost; // Actual cost to reach this node
    float heuristic; // Heuristic estimate to goal

    // Constructor for Node
    Node(int x, int y, float cost, float heuristic)
        : x(x), y(y), cost(cost), heuristic(heuristic) {}

    // Calculate the total cost (cost + heuristic)
    float totalCost() const {
        return cost + heuristic;
    }

    // Define operator< for priority_queue comparison
    bool operator<(const Node& other) const {
        return totalCost() > other.totalCost(); // Note: greater than for min-heap
    }
};


class Maze : public QObject
{
    Q_OBJECT

public:
    Maze(int = 10, int = 10, int = 50);
    virtual ~Maze() {};
    void setStartX(int newValue);
    void setStartY(int newValue);
    void setEndX(int newValue);
    void setEndY(int newValue);
    void setCellSize(int newValue);
    int getCanvasHeight() const;
    int getCanvasWidth() const;
    void drawInitialMaze(QPainter *p);
    void drawMaze(QPainter *p);
    void loadMazeFromFile(QString &filename);
    int solveMaze(QPainter *p, int alg);
    int DFS(QPainter *p);
    int BFS(QPainter *p);
    int Dijkstra(QPainter *p);
    int AStar(QPainter *p);
    void resetBFS();
    void resetDFS();

signals:
    void mazeLoaded();

private:
    std::vector<std::vector<int>> maze;
    std::stack<std::pair<int, int>> stack;
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<bool>> visited;
    std::vector<std::vector<std::pair<int, int>>> parent; // For BFS path reconstruction
    std::set<std::pair<int, int>> splitPoints; // For BFS where the path splits in at least 2
    std::vector<std::vector<float>> distances; // For Dijkstra and A*
    std::priority_queue<Node> openList;
    bool isValid(int x, int y);
    void colorPath(QPainter *p);
    void colorPathBack(QPainter *p, int x, int y);
    const int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int startX=1, startY=1, endX=5, endY=5, width, height, cellSize;
    bool solving = false;


};


#endif // MAZE_H
