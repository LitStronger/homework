#include <iostream>
#include <string>
using namespace std;
class animal
{
public:
    // char name[8];
    string name;
    float len;
    float weight;
};

class ter_animal: virtual public animal
{
public:
    float run_speed;
};

class aqu_animal: virtual public animal
{
public:
    float swim_speed;
};

class amp_animal:public ter_animal, public aqu_animal
{
public:
    
};

int main()
{
    animal a;
    ter_animal ter_a;
    aqu_animal aqu_a;
    amp_animal amp_a;
    cout<<sizeof(a)<<endl;
    cout<<sizeof(ter_a)<<endl;
    cout<<sizeof(aqu_a)<<endl;
    cout<<sizeof(amp_a)<<endl;

    // amp_a.name = "amp1";
    // amp_a.len = 10;
    amp_a.weight = 20;
    amp_a.run_speed = 30;
    amp_a.swim_speed = 40;

    // cout<<"name: "<<amp_a.name<<endl;
    // cout<<"len: "<<amp_a.len<<endl;
    cout<<"weight: "<<amp_a.weight<<endl;
    cout<<"run_speed: "<<amp_a.run_speed<<endl;
    cout<<"swim_speed: "<<amp_a.swim_speed<<endl;


    // string str1;
    // char str2[8];
    // cout<<sizeof(str1)<<" "<<sizeof(str2)<<endl;
    return 0;
}