#include<iostream>
using namespace std;
int odd(int num){
    return 3*num+1;
}
int even(int num){
    return num/2;
}
int main()
{
    int n=3,count=0;
    while(n!=1){
        count++;
        if(n%2==0){
            n=even(n);
        }
        else{
            n=odd(n);
        }
    }
    printf("%d",count);
    return 0;
}
