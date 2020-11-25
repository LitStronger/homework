#include <iostream>
#include <cmath>
// #include "point.h"
using namespace std;
class Point
{
public:
    Point(float new_x, float new_y)
    {
        x = new_x;
        y = new_y;
    }
    float get_x() { return x; }
    float get_y() { return y; }
    float friend line_fit(Point p[], int point_num);

private:
    float x, y;
};

float line_fit(Point p[], int point_num)
{
    float avg_x = 0, avg_y = 0, L_xx = 0, L_yy = 0, L_xy = 0; //avg 平均
    for (int i = 0; i < point_num; i++)
    {
        avg_x += p[i].x / point_num;
    }
    for (int i = 0; i < point_num; i++)
    {
        L_xx += (p[i].x - avg_x) * (p[i].x - avg_x);
        L_yy += (p[i].y - avg_y) * (p[i].y - avg_y);
        L_xy += (p[i].x - avg_x) * (p[i].y - avg_y);
    }
    cout << "model: y=ax+b." << endl;
    cout << "a=" << L_xy / L_xx;                          //输出回归系数a
    cout << " b=" << avg_y - L_xy * avg_x / L_xx << endl; //输出回归系数b
    return float(L_xy / sqrt(L_xx * L_yy));               //返回相关系数r
}

int main()
{
    Point l_p[10] = {Point(6, 10), Point(14, 20), Point(26, 30),
                     Point(33, 40), Point(46, 50), Point(54, 60), Point(67, 70),
                     Point(75, 80), Point(84, 90), Point(100, 100)}; //初始化数据点
    line_fit(l_p, 10);                                     //进行线性回归计算
}