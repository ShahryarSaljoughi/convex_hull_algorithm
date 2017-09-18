#include "my_algo.h"
#include "points.h"
#include "mainwindow.h"
#include <QApplication>
#include <random>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QVector>


using namespace std;
int main(int argc, char *argv[])
{

/*
    for(int j=0; j<10; j++){
        double random_x = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/100));
        double random_y = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/100));
        point z= {random_x, random_y };
        test_points.push_back(z);
    }

    for(point p: test_points) {
        res = 0;
        my_algo_v3(testy, res);
        std::cout<<endl<<endl<<endl<<res<<endl<<endl;
        testy.push_back(p);
    }
*/



    //MainWindow::drawGraph(x_plot, y_plot);

    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
