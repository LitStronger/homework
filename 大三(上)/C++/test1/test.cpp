#include <iostream>
#include <iomanip>
using namespace std;
int mult(int p, int q){
    for(int i = 1; i <= p; i++){
        for(int j = 1; j <= q; j++){
            cout<<i<<"*"<<j<<"="<<i*j<<"\t";
        }
        cout<<endl;
    }
}
float temConvert(float F){
    float C = (F-32)/1.8;
    return C;
}
int main(){
    // int row, col;
    // cin>>row>>col;   
    // mult(row, col);

    for(int i = 0; i <= 100; i += 5){
        cout<<setw(8)<<temConvert((float)i)<<"  ";
        if(i%2 == 1){
            cout<<endl;
        }
    }
    return 0;
}