#include <iostream>
#include <string>
using namespace std;

class Complex
{
public:
    Complex(float new_a)
    {
        a = new_a;
        b = 0;
    }
    Complex(float new_a, float new_b)
    {
        a = new_a;
        b = new_b;
    }

    void add(Complex new_c)
    {
         a += new_c.a;
         b += new_c.b;
    }
    void show()
    {
        cout<<a<<" + "<<b<<"i"<<endl;
    }

private:
    float a;
    float b;
};
int main()
{
    Complex c1(3,5);
    Complex c2(4);
    c1.add(c2);
    c1.show();
    return 0;
}