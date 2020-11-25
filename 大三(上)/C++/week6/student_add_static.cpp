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
        stu_num++;
    }
    static int get_stu_num()
    {
        return stu_num;
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
    static int stu_num;
};

int Student::stu_num = 0;
// int Student::get_stu_num(){
//     return stu_num;
// }

int main()
{
    char id1[10] = "001";
    char name1[10] ="no.1";
    char id2[10] = "002";
    char name2[10] ="no.2";

    Student stu1(id1, name1, 3);
    cout<<Student::get_stu_num()<<endl;
    stu1.print_all_msg();
    Student stu2(id2, name2, 3);
    cout<<Student::get_stu_num()<<endl;
    stu2.print_all_msg();

    return 0;
}