#include "my_algo.h"
#include "points.h"
#include "mainwindow.h"
#include <QApplication>
#include <random>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;
int main(int argc, char *argv[])
{
    int res=0;

    vector<point> testy={
        {4.4, 14},
        {6.7, 15.25},
        {6.9, 12.8},
        {2.1, 11.1},
        {9.5, 14.9},
        {13.2, 11.9},
        {10.3, 12.3},
        {6.8, 9.5},
        {3.3, 7.7},
        {0.6, 5.1},
        {5.3, 2.4},
        {8.45, 4.7},
        {11.5, 9.6},
        {13.8, 7.3},
        {12.9, 3.1},
        {11, 1.1}
    };

    //making other random points :
    srand((int)time(0));
    vector<point> test_points;
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

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
