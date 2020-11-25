#include <iostream>
using namespace std;
class Shape
{
public:
    Shape()
    {
        width = 0;
        height = 0;
    }
    float get_area();

private:
    float width;
    float height;
};

class Rectangle : public Shape
{
public:
    Rectangle()
    {
        width = 0;
    }
    Rectangle(float new_w, float new_h)
    {
        width = new_w;
        height = new_h;
    }
    float get_area()
    {
        return width * height;
    }

private:
    float width;
    float height;
};

class Circle : public Shape
{
public:
    Circle(float new_r)
    {
        radius = new_r;
    }
    float get_area()
    {
        return 3.14 * radius * radius;
    }

private:
    float radius;
};
class Square : public Rectangle
{
public:
    Square(float new_r)
    {
        width = new_r;
    }
    float get_area()
    {
        return width * width;
    }

private:
    float width;
};

int main()
{
    Circle c(3);
    Rectangle r(5, 6);
    Square s(5);
    cout << "Circle Area: " << c.get_area() << endl;
    cout << "Rectangle Area: " << r.get_area() << endl;
    cout << "Square Area: " << s.get_area() << endl;

    return 0;
}