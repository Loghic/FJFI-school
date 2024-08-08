#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QSpinBox>
#include <QMessageBox>
#include <QTimer>
#include <QComboBox>

#include <maze.h>

class MazeSolver : public QMainWindow
{
    Q_OBJECT

    Maze *maze;
    QWidget *wMain;
    QVBoxLayout *lMenu, *lStart, *lEnd;
    QHBoxLayout *lStartCoord, *lEndCoor, *lMain, *lCellSize, *lSpeed;
    QLabel *lblMaze, *lblStartingCoord, *lblEndCoord, *lblCellSize, *lblSpeed;
    QPainter *painter;
    QPixmap *canvas;
    QComboBox *cbAlgorithms;
    QPushButton *btnLoadFile, *btnSolve, *btnReset;
    QSpinBox *sbStartX, *sbStartY, *sbEndX, *sbEndY, *sbCellSize, *sbSpeed;
    QTimer *tTimer;

    void repaintMaze();

private slots:
    void onLoadFileClicked();
    void onCellSizeChanged();
    void onMazeLoaded();
    void onSolveClicked();
    void onCoordsChanged();
    void onSbSpeedChange();
    void onTimeout();
    void onResetClicked();
    void onAlgorthimsChanged();


public:
    MazeSolver(QWidget *parent = nullptr);
    ~MazeSolver();
};
#endif // MAZESOLVER_H
