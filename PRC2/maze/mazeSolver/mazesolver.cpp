#include "mazesolver.h"

#include <QFileDialog>

MazeSolver::MazeSolver(QWidget *parent)
    : QMainWindow(parent)
{
    maze = new Maze();
    canvas = new QPixmap(maze->getCanvasWidth(), maze->getCanvasHeight());
    painter = new QPainter(canvas);
    painter->setRenderHint(QPainter::Antialiasing);

    sbStartX = new QSpinBox();
    sbStartX->setRange(0, 100);
    sbStartX->setValue(1);
    sbStartY = new QSpinBox();
    sbStartY->setRange(0, 100);
    sbStartY->setValue(1);
    sbEndX = new QSpinBox();
    sbEndX->setRange(0, 100);
    sbEndX->setValue(5);
    sbEndY = new QSpinBox();
    sbEndY->setRange(0, 100);
    sbEndY->setValue(5);

    connect(sbStartX, SIGNAL(valueChanged(int)), this, SLOT(onCoordsChanged()));
    connect(sbStartY, SIGNAL(valueChanged(int)), this, SLOT(onCoordsChanged()));
    connect(sbEndX, SIGNAL(valueChanged(int)), this, SLOT(onCoordsChanged()));
    connect(sbEndY, SIGNAL(valueChanged(int)), this, SLOT(onCoordsChanged()));

    lblStartingCoord = new QLabel("Starting coordinatios");
    lStartCoord = new QHBoxLayout();
    lStartCoord->addWidget(sbStartX);
    lStartCoord->addWidget(sbStartY);
    lStart = new QVBoxLayout();
    lStart->addWidget(lblStartingCoord);
    lStart->addLayout(lStartCoord);

    lblEndCoord = new QLabel("End coordinatios");
    lEndCoor = new QHBoxLayout();
    lEndCoor->addWidget(sbEndX);
    lEndCoor->addWidget(sbEndY);
    lEnd = new QVBoxLayout();
    lEnd->addWidget(lblEndCoord);
    lEnd->addLayout(lEndCoor);

    sbCellSize = new QSpinBox();
    sbCellSize->setValue(50);
    sbCellSize->setRange(1, 100);
    sbCellSize->setSingleStep(5);

    lblCellSize = new QLabel("Cell Size");

    lCellSize = new QHBoxLayout();
    lCellSize->addWidget(lblCellSize);
    lCellSize->addWidget(sbCellSize);

    connect(sbCellSize, SIGNAL(valueChanged(int)), this, SLOT(onCellSizeChanged()));

    sbSpeed = new QSpinBox();
    sbSpeed->setRange(0, 1000);
    sbSpeed->setSingleStep(50);
    sbSpeed->setValue(200);
    lblSpeed = new QLabel("Solving speed (in ms");

    connect(sbSpeed, SIGNAL(valueChanged(int)), this, SLOT(onSbSpeedChange()));

    lSpeed = new QHBoxLayout();
    lSpeed->addWidget(lblSpeed);
    lSpeed->addWidget(sbSpeed);

    cbAlgorithms = new QComboBox();
    cbAlgorithms->addItem("DFS");
    cbAlgorithms->addItem("BFS");
    cbAlgorithms->addItem("A*");

    connect(cbAlgorithms, SIGNAL(currentIndexChanged(int)), this, SLOT(onAlgorthimsChanged()));

    btnLoadFile = new QPushButton("Load File");
    btnSolve = new QPushButton("Solve");
    btnReset = new QPushButton("Reset");

    connect(btnLoadFile, SIGNAL(clicked(bool)), this, SLOT(onLoadFileClicked()));
    connect(btnSolve, SIGNAL(clicked(bool)), this, SLOT(onSolveClicked()));
    connect(btnReset, SIGNAL(clicked(bool)), this, SLOT(onResetClicked()));

    lMenu = new QVBoxLayout();
    lMenu->addLayout(lStart);
    lMenu->addLayout(lEnd);
    lMenu->addLayout(lCellSize);
    lMenu->addLayout(lSpeed);
    lMenu->addWidget(cbAlgorithms);
    lMenu->addWidget(btnLoadFile);
    lMenu->addWidget(btnSolve);
    lMenu->addWidget(btnReset);
    lMenu->addStretch();

    connect(maze, SIGNAL(mazeLoaded()), this, SLOT(onMazeLoaded()));



    lblMaze = new QLabel();
    maze->drawInitialMaze(painter);
    lblMaze->setPixmap(*canvas);
    lblMaze->adjustSize();

    lMain = new QHBoxLayout();
    lMain->addWidget(lblMaze, 0, Qt::AlignCenter);
    lMain->addLayout(lMenu);


    wMain = new QWidget();
    wMain->setLayout(lMain);
    this->setCentralWidget(wMain);
    this->setWindowTitle("Maze solver");

    tTimer = new QTimer();
    tTimer->setInterval(200);

    connect(tTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));


}

void MazeSolver::repaintMaze()
{

    // Draw the maze to the scaled pixmap
    maze->drawMaze(painter);

    // Scale the pixmap to fit the label
    canvas->scaled(lblMaze->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Set the scaled pixmap to the label
    lblMaze->setPixmap(*canvas);
    lblMaze->adjustSize();
}

void MazeSolver::onLoadFileClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open PBM File", QString(), "PBM Files (*.pbm);;All Files (*)");
    if (!filePath.isEmpty()) {
        maze->loadMazeFromFile(filePath);
        repaintMaze();
    }
}

void MazeSolver::onCellSizeChanged()
{
    maze->setCellSize(sbCellSize->value());
    delete painter;
    delete canvas;
    canvas = new QPixmap(maze->getCanvasWidth(), maze->getCanvasHeight());
    painter = new QPainter(canvas);
    painter->setRenderHint(QPainter::Antialiasing);
    repaintMaze();
}


void MazeSolver::onMazeLoaded()
{
    this->onCellSizeChanged();
}

void MazeSolver::onSolveClicked()
{
    tTimer->start();
    btnSolve->setEnabled(false);
}

void MazeSolver::onCoordsChanged()
{
    maze->setStartX(sbStartX->value());
    maze->setStartY(sbStartY->value());
    maze->setEndX(sbEndX->value());
    maze->setEndY(sbEndY->value());
    onCellSizeChanged();
}

void MazeSolver::onSbSpeedChange()
{
    tTimer->setInterval(sbSpeed->value());
}

void MazeSolver::onTimeout()
{
    int solved = maze->solveMaze(painter, cbAlgorithms->currentIndex());
    if (solved != 0){
        QString result = (solved == 1) ? "Destination reached!" : "Destination is unreachable!";
        tTimer->stop();
        btnSolve->setEnabled(true);
        lblMaze->setPixmap(*canvas);
        QMessageBox::information(this, "Solution", result);
    }else{
        lblMaze->setPixmap(*canvas);
    }
}

void MazeSolver::onResetClicked()
{
    // Stop the timer if it's running
    tTimer->stop();

    // Enable the Solve button
    btnSolve->setEnabled(true);

    // Reset start and end coordinates to their default values (optional)

    // Clear the canvas and re-draw the initial maze
    delete painter;
    delete canvas;
    canvas = new QPixmap(maze->getCanvasWidth(), maze->getCanvasHeight());
    painter = new QPainter(canvas);
    painter->setRenderHint(QPainter::Antialiasing);

    maze->drawMaze(painter);

    // Reset DFS and BFS-specific state
    maze->resetDFS(); // Reset DFS-related state
    maze->resetBFS(); // Reset BFS-related state

    // Update the QLabel to show the reset maze
    lblMaze->setPixmap(*canvas);
    lblMaze->adjustSize();
}

void MazeSolver::onAlgorthimsChanged()
{
    maze->resetBFS();
    maze->resetDFS();
    onCellSizeChanged();
}



MazeSolver::~MazeSolver()
{
    delete painter;
    delete maze;
    delete canvas;
}
