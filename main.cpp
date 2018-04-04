#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Point{
public:
    double x, y;
    Point(float x, float y) : x(x), y(y) {}
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
}

void func(bool use,int index,double last_used_x,double max_x, double current,int num_used){
    if(index == num_points - 1 || num_used == max_points){
        current += ((use)? (points[index].x - last_used_x)*points[index].y :0 );
        best = ((current > best)? current:best);
        return;
    }
    current += ((use)? (points[index].x - last_used_x)*points[index].y :0 );
    double upper_bound = current + (max_x - points[index].x )*points[index].y;
    last_used_x = ((use)? points[index].x:last_used_x);
    if(upper_bound < best) return;

    func(false,index+1,last_used_x,max_x,current,num_used);
    if(num_used>=max_points){
        func(true,index+1,last_used_x,max_x,current,num_used+1);
    }
}


int main() {
    input();
    sort(points.begin(), points.end(), less_than_key());
    best = 0.0;
    for(int i=0;i<num_points;i++) {
        printf("%.12f %.12f\n",points[i].x,points[i].y );
    }
    if(max_points != 0){
        cout<<(int)points.size()-1;
        double max_x = points[(int)points.size()-1].x;
        printf("\n\n%.12f\n\n\n",max_x );
        func(false,0,0.0,max_x,0.0,0);
        func(true,0,0.0,max_x,0.0,0);
    }
    printf("%.12f\n",best );
    return 0;
}