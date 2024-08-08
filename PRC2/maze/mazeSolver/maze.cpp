#include "maze.h"

#include <QFile>
#include <iostream>

Maze::Maze(int w, int h, int cellS)
    : width(w), height(h)
{
    setCellSize(cellS);
}

void Maze::setStartX(int newValue)
{
    startX = qMin(qMax(0, (int)newValue), (int)width-1);
}
void Maze::setStartY(int newValue)
{
    startY = qMin(qMax(0, (int)newValue), (int)height-1);
}
void Maze::setEndX(int newValue)
{
    endX = qMin(qMax(0, (int)newValue), (int)width-1);
}
void Maze::setEndY(int newValue)
{
    endY = qMin(qMax(0, (int)newValue), (int)height-1);
}

void Maze::setCellSize(int newValue)
{
    cellSize = qMax(0, (int)newValue);
}

int Maze::getCanvasHeight() const{
    return height*cellSize;
}

int Maze::getCanvasWidth() const{
    return width*cellSize;
}

void Maze::drawInitialMaze(QPainter *p)
{
    const int startingMaze[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };


    height = sizeof(startingMaze) / sizeof(startingMaze[0]);
    width = sizeof(startingMaze[0]) / sizeof(startingMaze[0][0]);

    maze.resize(height, std::vector<int>(width, 0));

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            maze[row][col] = startingMaze[row][col];
        }
    }

    drawMaze(p);
}

void Maze::drawMaze(QPainter *p)
{
    p->setBrush(Qt::white);
    p->drawRect(0, 0, width * cellSize, height * cellSize);
    for(int row = 0; row < height; ++row)
    {
        for(int col = 0; col < width; ++col)
        {
            if(row == startY && col == startX) // Correctly handle start position
            {
                p->setBrush(QColor(34,139,34)); // Forest green
            }
            else if(row == endY && col == endX) // Correctly handle end position
            {
                p->setBrush(QColor(232,97,0)); // Spanish orange
            }
            else if(maze[row][col] == 0) // Wall
            {
                p->setBrush(Qt::black);
            }
            else // Path
            {
                p->setBrush(Qt::white);
            }
            p->drawRect(col * cellSize, row * cellSize, cellSize, cellSize); // Correct drawing coordinates
        }
    }
}

void Maze::loadMazeFromFile(QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        throw QString("Unable to open file");
    }
    QTextStream stream(&file);
    QString format = stream.readLine();
    if(format != "P1")
    {
        throw QString("File has wrong format");
    }
    QStringList size = stream.readLine().split(" ");
    int newWidth = size.at(0).toInt();
    int newHeight = size.at(1).toInt();
    width = newWidth;
    height = newHeight;
    maze.clear();
    maze.resize(newHeight, std::vector<int>(newWidth, 0));
    for(int row = 0; row < newHeight; row++)
    {
        QString line = stream.readLine();
        QStringList values = line.split(" ");
        for(int col = 0; col < newWidth; col++)
        {
            maze[row][col] = values.at(col).toInt();
        }
    }
    file.close();
    emit mazeLoaded();
}

int Maze::DFS(QPainter *p)
{
    if (!solving)
    {
        // Initialize DFS parameters
        stack = std::stack<std::pair<int, int>>(); // Clear the stack
        visited.assign(height, std::vector<bool>(width, false)); // Reset visited matrix
        stack.push({startX, startY});
        visited[startY][startX] = true;
        solving = true;
    }

    if (stack.empty())
    {
        solving = false;
        return -1; // No solution found
    }

    auto [x, y] = stack.top();

    // Check if we've reached the end
    if (x == endX && y == endY)
    {
        solving = false;
        return 1; // Reached the destination
    }

    bool moved = false;
    p->setPen(QPen(QColor(196, 0, 0), cellSize / 4, Qt::SolidLine, Qt::RoundCap));

    // Explore neighbors
    for (const auto& dir : directions)
    {
        int newX = x + dir[0];
        int newY = y + dir[1];

        if (isValid(newX, newY))
        {
            // Draw line to the new cell
            p->drawLine(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2, newX * cellSize + cellSize / 2, newY * cellSize + cellSize / 2);

            visited[newY][newX] = true;
            stack.push({newX, newY});
            moved = true;
            break;
        }
    }

    if (!moved)
    {
        stack.pop();
        p->setPen(QPen(QColor(128, 128, 128), cellSize / 4, Qt::SolidLine, Qt::RoundCap));

        if (!stack.empty())
        {
            auto [prevX, prevY] = stack.top();
            // Draw line back to the previous cell
            p->drawLine(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2, prevX * cellSize + cellSize / 2, prevY * cellSize + cellSize / 2);
        }
    }

    return 0; // Continue exploring
}


bool Maze::isValid(int x, int y)
{
    return x >= 0 && x < width && y >= 0 && y < height && !visited[y][x] && maze[y][x] == 1;
}

int Maze::BFS(QPainter *p)
{
    if (!solving)
    {
        // Initialize BFS parameters
        queue = std::queue<std::pair<int, int>>(); // Clear the queue
        visited.assign(height, std::vector<bool>(width, false)); // Reset visited matrix
        parent.assign(height, std::vector<std::pair<int, int>>(width, {-1, -1})); // Reset parent matrix
        queue.push({startX, startY});
        splitPoints.clear(); // Clear split points
        visited[startY][startX] = true;
        solving = true;
    }

    if (queue.empty())
    {
        solving = false;
        return -1; // No solution found
    }

    auto [x, y] = queue.front();
    queue.pop();

    // Check if we've reached the end
    if (x == endX && y == endY)
    {
        solving = false;
        colorPath(p); // Color the path once we reach the destination
        return 1; // Reached the destination
    }

    bool moved = false;
    p->setPen(QPen(QColor(0, 0, 139), cellSize / 4, Qt::SolidLine, Qt::RoundCap));

    int numOfValidPaths = 0;
    for (const auto& dir : directions)
    {
        int newX = x + dir[0];
        int newY = y + dir[1];

        if (isValid(newX, newY) && !visited[newY][newX])
        {
            // Draw line to the new cell
            p->drawLine(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2, newX * cellSize + cellSize / 2, newY * cellSize + cellSize / 2);

            visited[newY][newX] = true;
            queue.push({newX, newY});
            parent[newY][newX] = {x, y}; // Track parent for path reconstruction
            moved = true;
            numOfValidPaths++;
        }
    }

    if(numOfValidPaths > 1){
        splitPoints.insert({x, y});
    }

    if (!moved)
    {
        // No valid moves, color the current cell gray
        p->setPen(QPen(QColor(128, 128, 128), cellSize / 4, Qt::SolidLine, Qt::RoundCap));

        // Draw the path back to the parent cell in gray
        colorPathBack(p, x, y);
    }

    return 0; // Continue exploring
}

void Maze::colorPathBack(QPainter *p, int x, int y)
{
    p->setPen(QPen(QColor(128, 128, 128), cellSize / 4, Qt::SolidLine, Qt::RoundCap));

    while (parent[y][x] != std::pair<int, int>{-1, -1})
    {
        auto [prevX, prevY] = parent[y][x];

        // Draw line from the current cell to the previous cell in gray
        p->drawLine(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2,
                    prevX * cellSize + cellSize / 2, prevY * cellSize + cellSize / 2);

        // Move to the previous cell
        x = prevX;
        y = prevY;

        // Check if we've reached a split point
        if (splitPoints.find(std::make_pair(x, y)) != splitPoints.end())
        {
            break; // Stop at the split point
        }
    }
}


void Maze::colorPath(QPainter *p)
{
    // Start from the end position and move backwards using the parent matrix
    int x = endX, y = endY;
    p->setPen(QPen(Qt::red, cellSize / 4, Qt::SolidLine, Qt::RoundCap));

    while (parent[y][x] != std::pair<int, int>{-1, -1})
    {
        int prevX = parent[y][x].first;
        int prevY = parent[y][x].second;

        // Draw line from the current cell to the previous cell in gray
        p->drawLine(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2, prevX * cellSize + cellSize / 2, prevY * cellSize + cellSize / 2);

        x = prevX;
        y = prevY;
    }
}

void Maze::resetBFS()
{
    // Clear BFS-specific state
    queue = std::queue<std::pair<int, int>>(); // Clear the queue
    visited.assign(height, std::vector<bool>(width, false)); // Reset visited matrix
    solving = false; // Set solving to false
}


void Maze::resetDFS()
{
    // Clear DFS-specific state
    stack = std::stack<std::pair<int, int>>(); // Clear the stack
    visited.assign(height, std::vector<bool>(width, false)); // Reset visited matrix
    solving = false; // Set solving to false
}

float heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}


int Maze::AStar(QPainter *p)
{
    if (!solving) // Check if the algorithm is already running
    {
        // Initialize A* parameters
        distances.assign(height, std::vector<float>(width, std::numeric_limits<float>::max()));
        parent.assign(height, std::vector<std::pair<int, int>>(width, {-1, -1}));
        visited.assign(height, std::vector<bool>(width, false));
        openList = std::priority_queue<Node>(); // Initialize priority queue
        solving = true;

        distances[startY][startX] = 0.0f;
        openList.push(Node(startX, startY, 0.0f, heuristic(startX, startY, endX, endY)));
    }

    if (openList.empty())
    {
        solving = false;
        return -1;
    }

    Node current = openList.top();
    openList.pop();

    int x = current.x;
    int y = current.y;

    if (visited[y][x])
    {
        // Skip already visited nodes
        return 0;
    }

    visited[y][x] = true;

    // Check if we've reached the end
    if (x == endX && y == endY)
    {
        colorPath(p); // Color the path from end to start
        solving = false;
        return 1; // Reached the destination
    }

    bool moved = false;
    p->setPen(QPen(QColor(0, 0, 139), cellSize / 4, Qt::SolidLine, Qt::RoundCap));

    int numOfValidPaths = 0;
    for (const auto& dir : directions)
    {
        int newX = x + dir[0];
        int newY = y + dir[1];

        if (isValid(newX, newY) && !visited[newY][newX])
        {
            float newCost = distances[y][x] + 1.0f; // Assume uniform cost for simplicity

            if (newCost < distances[newY][newX])
            {
                distances[newY][newX] = newCost;
                parent[newY][newX] = {x, y};
                float heuristicCost = heuristic(newX, newY, endX, endY);
                openList.push(Node(newX, newY, newCost, heuristicCost));

                // Draw line to the new cell
                p->drawLine(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2,
                            newX * cellSize + cellSize / 2, newY * cellSize + cellSize / 2);

                moved = true;
                numOfValidPaths++;
            }
        }
    }

    if(numOfValidPaths > 1){
        splitPoints.insert({x, y});
    }

    if (!moved)
    {
        // No valid moves, color the current cell gray
        p->setPen(QPen(QColor(128, 128, 128), cellSize / 4, Qt::SolidLine, Qt::RoundCap));

        // Draw the path back to the parent cell in gray
        colorPathBack(p, x, y);
    }

    return 0;
}



int Maze::solveMaze(QPainter *p, int alg)
{
    if (alg == 0){
        return DFS(p);
    }else if (alg == 1){
        return BFS(p);
    }else if (alg == 2){
        return AStar(p);
    }

    return -1;
}




