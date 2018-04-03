#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Point{
public:
    double x, y;
    Point(float x, float y) : x(x), y(y) {}
};

vector<Point> points;
int num_points, max_points;

void input(){
    double x,y;
    cin >> num_points >> max_points;
    cout << num_points << " " << max_points<<endl;
    double max = 0.0;
    for(int i=0;i<num_points;i++) {
        cin >> x >> y;
        Point p = Point(x,y);
        points.push_back(p);
        max = (((x*y)>max)? x*y:max);
    }
    for(int i=0;i<num_points;i++) {
        printf("%.12f %.12f\n",points[i].x,points[i].y );
    }
}


double overlap(Point n,Point x){

}

int main() {
    input();
    return 0;
}