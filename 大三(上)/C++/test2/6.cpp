#include <iostream>
using namespace std;

class Student
{
public:
    Student(char *new_id, char *new_name, int new_grade)
    {
        id = string(new_id);
        name = string(new_name);
        grade = new_grade;
    }

    void set_id(char *new_id)
    {
        id = string(new_id);
    }
    void set_name(char *new_name)
    {
        name = string(new_name);
    }
    void print_all_msg()
    {
        cout<<"id:"<<id<<" name:"<<name;
    }

private:
    string  id;
    string name;
    int grade;
};
int main()
{
    char * id = "1234567";
    char * name ="lyq";
    int grade = 3;
    Student stu(id, name, grade);
    stu.set_id("111111");
    stu.print_all_msg();
    return 0;
}