#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

#define NOW 2020

void reply(string s) {

    int index = s.find(' ');
    string first_name = s.substr(0, index);
    first_name = first_name[0];

    s = s.substr(index+1);
    index = s.find(' ');
    string last_name = s.substr(0, index);

    string birth = s.substr(index+1);

    cout<<first_name<<"-"<<last_name<<"-"<<birth<<endl;
    cout<<"Dear "<<first_name<<". "<<last_name<<","<<endl;
    cout<<"  Thank you for your message! We appreciate "                        \
    "the wonderful "<<NOW-atoi(birth.c_str())<<" years for your growing up. We will reply soon.\n\n" \
    "Best Wishes.\n"<<endl;
}

int main() {
    string s;
    cout << "input: ";
    getline(cin, s);
    reply(s);
    return 0;
}