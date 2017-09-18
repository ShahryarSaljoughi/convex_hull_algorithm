#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <vector>
#include <QVector>
#include <stdlib.h>
#include <QInputDialog>

#include "my_algo.h"

//using namespace std;

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

    int res=0;

    vector<point> testy={
        {4.4, 14},
        {6.7, 15.25},
    };
    srand((int)time(0));

    QVector<double> x_plot;
    QVector<double> y_plot;

    int number_of_points = QInputDialog::getInt(this, "", "enter number of points to reach");
    for(int i=0; i<number_of_points ; ++i){
        double random_x = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/100));
        double random_y = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/100));
        point z = {random_x, random_y};
        testy.push_back(z);
        res = 0;
        my_algo_v3(testy, res);
        x_plot.push_back(testy.size());
        y_plot.push_back(res);
    }


    qDebug()<<"\n\n\n    ";
    qDebug()<<"DATAs are:\n";
    for(int i=0; i<x_plot.size(); i++){
        qDebug()<< x_plot.at(i)<<" , "<<y_plot.at(i)<<" \n";
    }



    ui->customPlot->addGraph();

    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::white, 1));

    ui->customPlot->graph(0)->setData(x_plot, y_plot);

    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->xAxis->setRange(0, number_of_points+10);
    ui->customPlot->yAxis->setRange(0, res);

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

void MainWindow::drawGraph(QVector<double> x, QVector<double> y){

    ui->customPlot->addGraph();

    ui->customPlot->graph(0)->setData(x, y);

    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->xAxis->setRange(0, 6);
    ui->customPlot->yAxis->setRange(0, 6);

    ui->customPlot->replot();
}
