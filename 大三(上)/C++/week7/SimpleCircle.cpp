#include <iostream>
#define PI 3.14
using namespace std;
class SimpleCircle
{
public:
    SimpleCircle(float new_r)
    {
        r = new_r;
        its_radius = &r;
    }
    float cal_area()
    {
        return PI * (*its_radius) * (*its_radius);
    }
    float cal_perimeter()
    {
        return 2 * PI * (*its_radius);
    }

private:
    int r;
    int *its_radius;
};

int main()
{
    SimpleCircle R1(5);
    cout << "Area: " << R1.cal_area() << endl;
    cout << "Perimeter: " << R1.cal_perimeter() << endl;
    return 0;
}