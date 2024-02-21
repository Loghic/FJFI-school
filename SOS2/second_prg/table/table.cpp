#include "table.h"
#include "./ui_table.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display()
{
    for (int k = 0; k < N; k++) // k ... cislo sloupce
    {
        int i = a[k]; // ... cislo radky
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setText (QString::number (k));
        item->setBackground(QColor ("yellow").lighter());
        item->setForeground(QColor ("black")); // sets color of string inside
        ui->table->setItem(i,k,item);
    }
    stop = true;
}

void MainWindow::place(int k) // umisti damu na k-ty sloupec
{
    if (!stop)
    {
        for (int i = 0; i < N; i++){ // cyklus pro radky
            bool ok = true;
            for (int v = 1; v < k; v++)
                if (a[k-v] == i || a[k-v] == i-v || a[k-v] == i+v)
                    ok = false;
            if (ok){
                a[k] = i;
                if (k < N-1 && ! stop)
                    place (k+1);
                else
                    display();
            }
        }
    }
}

void MainWindow::on_actionRun_triggered()
{
    ui->table->setRowCount(N);
    ui->table->setColumnCount(N);

    int a [N];

    for (int i = 0; i < N; i++) a[i] = -1;
    stop = false;
    place(0);


//     for (int i = 0; i < ui->table->columnCount(); i++)
//     {
//         QTableWidgetItem * item = new QTableWidgetItem;
//         item->setText (QString::number (i));
//         item->setToolTip ("policko " + QString::number (i) + "," + QString::number(i));
//         item->setBackground(QColor ("yellow").lighter());
//         item->setForeground(QColor ("black")); // sets color of string inside
//         ui->table->setItem(i,i,item);
//     }
// }
}


void MainWindow::on_actionQuit_triggered()
{
    close();
}

