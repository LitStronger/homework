#include <iostream>
#include <cmath>
using namespace std;
class Point
{
public:
    Point(float new_x, float new_y, float new_z)
    {
        x = new_x;
        y = new_y;
        z = new_z;
        point_num++;
    }
    static int get_num()
    {
        return point_num;
    }
    float friend cal_area(Point &a, Point &b, Point &c);

private:
    float x, y, z;
    static int point_num;
};

int Point::point_num = 0;

float cal_area(Point &a, Point &b, Point &c)
{
    // 计算三边， 海伦公式求面积
    float edge_ab = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
    float edge_bc = sqrt((b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y) + (b.z - c.z) * (b.z - c.z));
    float edge_ac = sqrt((a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y) + (a.z - c.z) * (a.z - c.z));

    float p = (edge_ab + edge_bc + edge_ac) / 2;
    float s = sqrt(p * (p - edge_ac) * (p - edge_bc) * (p - edge_ac));
    return s;
}
int main()
{
    Point p1(1, 0, 0);
    Point p2(0, 1, 0);
    Point p3(0, 0, 1);
    cout << "sum:" << Point::get_num() << "area:" << cal_area(p1, p2, p3) << endl;
}