#include <iostream>
#include <algorithm>
using namespace std;
const int N=1000000;
int PARTITION(int *arr, int p, int r) {
    int x = arr[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (arr[j] <= x) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

void QUICKSORT(int *arr, int p, int r) {
    if (p < r) {
        int q = PARTITION(arr, p, r);
        QUICKSORT(arr, p, q - 1);
        QUICKSORT(arr, q + 1, r);
    }
}

int hash_char(char *str,int length) {
    int hash_value=0;

    for (int i = 0; i < length; ++i) {
        hash_value+=(str[i]-'a')^2;
    }

    return hash_value;
}

double myPow(double x, int n) {
    if (n == 0) { return 1; }
    if (n == 1) { return x; }
    if (n == -1) { return 1 / x; }
    double half = myPow(x, n / 2);
    double rest = myPow(x, n % 2);
    return rest * half * half;
}
class set{
public:
    int hash_char(char *str,int length){
        int hash_value=0;

        for (int i = 0; i < length; ++i) {
            hash_value+=(str[i]-'a')^2;
        }

        return hash_value;
    }
    void push(char *str, int length){
        int hash_value = hash_char(str,length);
        bool exist= false;
        for (int i = 0; i < size; ++i) {
            if (data[i] == hash_value){
                exist= true;
                break;
            }
        }
        if (!exist){
            data[size]=hash_value;
            size++;
        }
    };
    int length(){return size;};
    void print(){
        for (int i = 0; i < size; ++i) {
            cout<<data[i]<<" ";
        }
        cout<<endl;
    }

private:
    int data[N];
    int size=0;
};

int main(){
    int
}