//
// Created by caohch1 on 10/1/20.
//

#include<iostream>
#include <time.h>

using namespace std;

void generateRandomArray(int *arr, int n, int rangL, int rangR) {
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % (rangR - rangL + 1) + rangL;
    }
}

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

int main() {
    int length, k, res = 0;
    cin >> length >> k;
    int data[length];
    for (int i = 0; i < length; ++i) {
        cin >> data[i];
    }
//    srand(time(NULL));
//    int length=rand()%(1000000);
//    srand(time(NULL));
//    int k=rand()%(length-1);
//    int data[length];
//    generateRandomArray(data,length,1,1000000000);
//    int res=0;

//    time_t start,end;
//
//    start-clock();
    QUICKSORT(data, 0, length - 1);
    int diff[length - 1];
    for (int i = 0; i < length - 1; ++i) {
        diff[i] = data[i + 1] - data[i];
    }

    QUICKSORT(diff, 0, length - 2);
    for (int i = 0; i < k; ++i) {
        res += diff[i];
    }
    cout << res << endl;
//    end=clock();
//    cout<<"Time: "<<end-start;
    return 0;
}