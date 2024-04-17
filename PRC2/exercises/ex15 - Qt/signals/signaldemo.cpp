#include "signaldemo.h"
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

SignalDemo::SignalDemo(QWidget *parent)
    : QWidget(parent)
{
    setupForm();
}


void SignalDemo::setupForm(){
    QVBoxLayout *mainLayout = new QVBoxLayout; // lMain - main layout
    QHBoxLayout *firstLayout = new QHBoxLayout; // lTop - top layout

    slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0,100);
    slider->setValue(42);

    spinBox = new QSpinBox;
    spinBox->setRange(0,100);
    spinBox->setValue(42);

    closeBtn = new QPushButton(tr("Close Applicaiton"));

    firstLayout->addWidget(slider);
    firstLayout->addWidget(spinBox);
    mainLayout->addLayout(firstLayout);

    mainLayout->addStretch(); // This will push layout above and below it to opposite directions

    mainLayout->addWidget(closeBtn);
    this->setLayout(mainLayout); // in order to show slider and spinbox and other added stuff...

    setWindowTitle(tr("Signal and slot demonstration"));

    // QObject::connect(...)
    connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int))); //Moving slider changes value of spinBox
    connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int))); //this is vice-versa
    // connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(close()) ); // one possible way
    connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(readyToQuit()) ); // ready to quit our own funciton

    // connecting slider to our define slot in order to chech whether we have reached min or max
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(checkMinMax(int))); // either slider or spinbox may be connected since they are interconnected

}

void SignalDemo::checkMinMax(int value)
{
    qDebug() << value; // prints values to console
    if (value == slider->minimum()){
        QMessageBox::information(this, tr("Information"), tr("Minimum has been reached"));
    } else if (value == slider->maximum()){
        QMessageBox::information(this, tr("Information"), tr("Maximum has been reached"));
    }
}

void SignalDemo::readyToQuit()
{
    emit quitting();
}



SignalDemo::~SignalDemo() {}
