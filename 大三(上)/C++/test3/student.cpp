#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
    Student(char new_id[], char new_name[], int new_grade)
    {
        id = string(new_id);
        name = string(new_name);
        grade = new_grade;
    }

    void set_id(char new_id[])
    {
        id = string(new_id);
    }
    void set_name(char new_name[])
    {
        name = string(new_name);
    }
    void print_all_msg()
    {
        cout<<"id:"<<id<<" name:"<<name<<" grade:"<<grade<<endl;
    }

private:
    string  id;
    string name;
    int grade;
};
int main()
{
    char id[10] = "11111111";
    char name[10] ="lyq";
    int grade = 3;

    Student stu(id, name, grade);
    stu.print_all_msg();
    char new_id[10] = "22222222";
    stu.set_id(new_id);
    stu.print_all_msg();
    return 0;
}