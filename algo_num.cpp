/* this is an improved vesrion of the previous algorithm .
 */

#include <iostream>
#include <vector>
#include <list>
#include "points.h"
#include "polar_angle.h"
#include <math.h>

using namespace std;


bool operator!=(const point& p1, const point& p2)
{
    if (p1.x==p2.x && p2.y==p1.y){return false;}
    return true;
}

bool operator==(const point& p1, const point& p2)
{
    if (p1.x==p2.x && p2.y==p1.y){return true;}
    return false;
}

point get_top(vector<point> &points, int& sum){
    point p_top = points.at(0);
    for(point i : points){
        sum++;
        if (i.y>p_top.y){
            p_top = i;
        }else if(i.y==p_top.y and i.x>p_top.x){
            p_top = i;
        }
    }
    return p_top;
}

point get_P0(vector<point> &points, int& sum){

    point P0 = points.at(0);
    for(point i : points){
        sum++;
        if (i.y<P0.y){
            P0 = i;
        }else if(i.y==P0.y && i.x<P0.x){
            P0 = i;
        }
    }
    return P0;
}

void remove_inside_points(list<point> points, const point &l,const point &r, int& sum){
    cout<<"remove_inside_points() is running"<<endl;
    list<point> internal_points;
    for(point p: points){
        sum++;
        double determinant =  r.x*p.y - p.x*r.y +
                              p.x*l.y - l.x*p.y +
                              l.x*r.y - r.x*l.y ;
        if (determinant < 0) {
            internal_points.push_back(p);
            cout<<"("<<p.x<<", "<<p.y<<") is removed"<<endl;
        }
    }
    for(point p: internal_points) points.remove(p);
}

void find_next_vertices(const list<point> points, point &l, point &r, const point& p_top,
                        bool right_reached, bool left_reached, int& sum){
    cout<<"find_next_vertices is running"<<endl;

    list<point>::const_iterator it_l = points.begin();
    list<point>::const_iterator it_r = points.begin();


    while(!left_reached and(*it_l==l or (it_l->y) <l.y) and it_l!=points.end() and *it_l!=p_top) it_l++;
    while(!right_reached and (*it_r==r or (it_r->y) <r.y) and it_r!=points.end() and *it_r!=p_top) it_r++;


    point next_l = *it_l;
    point next_r = *it_r;

    for(point p: points){
        sum++;
        if ((p!=l) and (p.y>=l.y) and (polar_angle(l, p)<=M_PI)and
                (polar_angle(l, p)>polar_angle(l, next_l))) next_l = p;
        if ((p!=r) and (p.y>=r.y) and (polar_angle(r, p)<polar_angle(r, next_r))) next_r = p;
    }

    if(right_reached) next_r= p_top;
    if(left_reached) next_l= p_top;

    l=next_l;
    r=next_r;
    cout<<"new left vertex ("<<l.x<<", "<<l.y<<")"<<endl;
    cout<<"new right vertex ("<<r.x<<", "<<r.y<<")"<<endl;
}

vector<point> my_algo_v3(vector<point> &input, int& sum){

    // later this list-vector thing will be solved!
    list<point> points ;
    for(point p: input) points.push_back(p);

    vector<point> vertices;
    point right_vertex;
    point left_vertex;

    point P0 = get_P0(input, sum);
    point p_top = get_top(input, sum);

    vertices.push_back(P0);
    vertices.push_back(p_top);
    right_vertex = left_vertex = P0;
    points.remove(P0);

    cout<<"P0 is ("<<P0.x<<" , "<<P0.y<<") "<<endl;


    bool right_reached = false;
    bool left_reached = false;

    while(left_vertex != p_top or right_vertex != p_top){
        cout<<"while is running"<<endl;
        find_next_vertices(points, left_vertex, right_vertex, p_top, right_reached, left_reached, sum);

        if (left_vertex==p_top) left_reached = true;
        if (right_vertex==p_top) right_reached = true;

        if (left_vertex!=p_top) vertices.push_back(left_vertex);
        if (right_vertex!=p_top) vertices.push_back(right_vertex);




        remove_inside_points(points, left_vertex, right_vertex, sum);
        cout<<"("<<right_vertex.x<<","<<right_vertex.y<<") found on right side"<<endl;
        cout<<"("<<left_vertex.x<<","<<left_vertex.y<<") found on left side"<<endl;
        if (left_vertex!=p_top) points.remove(left_vertex);
        if (right_vertex!=p_top)points.remove(right_vertex);
    }

    return vertices;
}
