#include<iostream>
using namespace std;

int main()
{
    int i;
    for(i=32;i<100;i++){
        int pow2 = i*i;
        if(pow2/1000==(pow2/100)%10 && (pow2/10)%10==pow2%10)
        {
            printf("%d",pow2);
        }
    }
    return 0;
}