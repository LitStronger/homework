#include <iostream>
#include <string.h>
using namespace std;
class Car;
class Boat{
public:
    Boat(float w){
        weight = w;
    }
    friend float getTotalWeight(Boat &b, Car &c);
private:
    float weight;
};

class Car{
public:
    Car(float w){
        weight = w;
    }
    friend float getTotalWeight(Boat &b, Car &c);
private:
    float weight;
};
float getTotalWeight(Boat &b, Car &c){
        return b.weight+c.weight;

} 
int main()
{
    Boat b(100.1);
    Car c(200.2);
    cout<<getTotalWeight(b, c)<<endl;
    return 0;
}