#include<iostream>
using namespace std;
int factorial(int num, int res){
    if(num==1){
        return res;
    }
    
    factorial(num-1, res*(num));
}
int main()
{
    int i,n,sum=0;
    //factorial(3,res);
    cin >> n;
    for(i=1;i<=n;i++){
       sum += factorial(i, 1);
    }
    printf("%d",sum);
    return 0;
}