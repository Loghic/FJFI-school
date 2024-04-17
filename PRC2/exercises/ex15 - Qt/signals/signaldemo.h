#ifndef SIGNALDEMO_H
#define SIGNALDEMO_H

#include <QWidget>

class QSpinBox;
class QSlider;
class QPushButton;

class SignalDemo : public QWidget
{
    Q_OBJECT
    QSpinBox *spinBox;
    QSlider *slider;
    QPushButton *closeBtn; //btnQuit
    void setupForm();

private slots:
    void readyToQuit();
    void checkMinMax(int);

public:
    SignalDemo(QWidget *parent = nullptr);
    ~SignalDemo();

signals:
    void quitting();
};
#endif // SIGNALDEMO_H
