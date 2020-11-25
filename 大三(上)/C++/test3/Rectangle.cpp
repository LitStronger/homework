#include <iostream>
#include <string>
using namespace std;

class Rectangle
{
public:
    Rectangle()
    {
        width = 1.0;
        height = 1.0;
    }
    Rectangle(float new_width, float new_height)
    {
        width = new_width;
        height = new_height;
    }

    float calcu_S()
    {
        return width * height;
    }

private:
    float width;
    float height;
};
int main()
{
    Rectangle R1;
    float s = R1.calcu_S();
    cout<<s<<endl;
    Rectangle R2(2,2);
    float s2 = R2.calcu_S();
    cout<<s2<<endl;
    return 0;
}