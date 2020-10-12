#include <iostream>

using namespace std;

const int N = 500010;

class stack {
private:
    int arr[N];
    int size = 0;
public:
    bool empty() { return (size == 0) ; };

    int top() { return arr[size - 1]; };

    void pop() {
        size--;
    };

    void push(int num) {
        arr[size] = num;
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
        cin >> data[i];
    }

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
    cout << fin << endl;

    return 0;
}