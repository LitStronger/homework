#include <iostream>
#include <iomanip>
using namespace std;
float find_max(float * num){
    int i, max = num[0];
    for(i=1; num[i]!='\0'; i++){
        if(num[i] > max){
            max = num[i];
        }
    }
    return max;
}
float find_min(float * num){
    int i, min = num[0];
    for(i=1; num[i]!='\0'; i++){
        if(num[i] < min){
            min = num[i];
        }
    }
    return min;
}
float get_avg(float * num){
    int i;
    float sum = 0, avg = 0;
    for(i=0; num[i]!='\0'; i++){
        sum += num[i];
    }
    avg = sum/i;
    return avg;
}
int main()
{
    int n;
    float min, max, avg;
    float num[100];
    cout<<"input mount of n: ";
    cin >> n;
    cout<<"input n: ";
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    max = find_max(num);
    min = find_min(num);
    avg = get_avg(num);
    cout << "max: " << max << endl;
    cout << "min: " << min << endl;
    cout << "average: " << avg << endl;
    return 0;
}