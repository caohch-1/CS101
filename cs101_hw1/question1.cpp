#include <iostream>

using namespace std;

void generateRandomArray(int *arr, int n, int rangL, int rangR) {
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % (rangR - rangL + 1) + rangL;
    }
}

const int N = 500010;

class stack{
private:
    int arr[N];
    int size=0;
public:
    bool empty(){ return (size==0)? true: false;};
    int top(){return arr[size-1];};
    void pop(){
        size--;
    };
    void push(int num){
        arr[size]=num;
        size++;
    }

};


int main() {
/*Input test*/

    //get length
    int length;
    cin >> length;
    //get queue
    int data[length];
    for (int i = 0; i < length; ++i) {
        cin>>data[i];
    }

/*Random test*/

//    srand(time(NULL));
//    int length = rand() % (500000);
//    int data[length];
//    generateRandomArray(data, length, 1, 10000);
//    for (int i = 0; i < length; ++i) {
//        cout << data[i] << " ";
//    }
//    cout << endl;

/*Certain data test*/

//    int length=16;
//    int data[length]={77 ,42 ,46 ,90 ,90 ,97 ,47 ,79 ,69 ,32 ,75 ,27 ,92 ,48 ,34 ,99 };

    int fin = 0;
    stack stk;
    int repeat[length];
    for (int i = 0; i < length; ++i) {
        repeat[i] = 1;
        while (!stk.empty() && data[i] >= data[stk.top()]) {
            if (data[i] != data[stk.top()]) {
                fin += repeat[stk.top()];
                stk.pop();
            } else {
                repeat[i] += repeat[stk.top()];
                fin += repeat[stk.top()];
                stk.pop();
            }
        }
        if (!stk.empty()) fin++;
        stk.push(i);
    }
    cout<< fin << endl;

    return 0;
}