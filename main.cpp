#include <iostream>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class Point{
public:
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};


struct less_than_key
{
    inline bool operator() (const Point &point1, const Point &point2)
    {
        return (point1.y > point2.y);
    }
};

vector<Point> points;
int num_points, max_points;
double best;
double max_x;
double smaller_loss;
double total;

void input(){
    double x,y;
    cin >> num_points >> max_points;
    for(int i=0;i<num_points;i++) {
        cin >> x >> y;
        Point p = Point(x,y);
        points.push_back(p);
    }
}

void f(bool use,int index,double last_used_x, double current,int num_used,double loss) {
    if((num_points - 1 - index) < max_points - num_used ) return;
    if (index == num_points - 1 || num_used == max_points) {
        if (use) {
            current = current + ((points[index].x - last_used_x) * points[index].y);
            last_used_x = points[index].x;
        }else{
            loss = loss + (points[index].x - last_used_x)*(points[index].y);
        }
        if(current > best){
            best = current;
            smaller_loss = total - current;
        }
        return;
    } else {
        if (use) {
            current = current + ((points[index].x - last_used_x) * points[index].y);
            last_used_x = points[index].x;
        }else{
            loss = loss + (points[index].x - last_used_x)*(points[index].y-points[index+1].y);
        }
        if(loss >= smaller_loss) return;
        f(true,index+1,last_used_x,current,num_used+1,loss);
        f(false,index+1,last_used_x,current,num_used,loss);
    }
}


int main() {
    total = 0.0;
    input();
    sort(points.begin(), points.end(), less_than_key());
    total = points[0].x*points[0].y;
    for(int i = 1; i < (int)points.size();i++){
        total += (points[i].x-points[i-1].x)*points[i].y;
    }
    best = 0.0;
    smaller_loss = total;
    if(max_points != 0 && num_points != 0){
        max_x = points[(int)points.size()-1].x;
        f(false,0,0.0,0.0,0,0.0);
        f(true,0,0.0,0.0,1,0.0);
    }
    printf("%.12f\n",best );
    return 0;
}