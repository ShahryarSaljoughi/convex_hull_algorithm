#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->exitBu,
            &QPushButton::clicked,
            this, &MainWindow::close
            );
    connect(
                ui->runBu, &QPushButton::clicked,
                this, &MainWindow::draw
                );
    connect(
                ui->xRange, &QLineEdit::textChanged, this, &MainWindow::setXRange
                );
    connect(
                ui->yRange, &QLineEdit::textChanged, this, &MainWindow::setYRange
            );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw(){
    qDebug()<<"drawing a graph";
    QVector<double> x(101), y(101);


    for(int i=0; i<6; ++i) {
        x[i] = i;
        y[i] = x[i]*x[i];
    }

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);

    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->xAxis->setRange(0, 6);
    ui->customPlot->yAxis->setRange(0, 6);

    ui->customPlot->replot();
}

void MainWindow::setXRange(QString text){
    this->ui->customPlot->xAxis->setRange(0, text.toDouble());
    this->ui->customPlot->replot();
}


void MainWindow::setYRange(QString text){
    this->ui->customPlot->yAxis->setRange(0, text.toDouble());
    this->ui->customPlot->replot();
}
