#include <iostream>
using namespace std;
const unsigned int C=33;
unsigned int hashMod(unsigned int n, unsigned int m){
    unsigned int shift=(32-m)/2;
    return ((C*n)>>shift)&((1<<m)-1);
}

int main(){
    cout<<hashMod(7263,8)<<endl;
}