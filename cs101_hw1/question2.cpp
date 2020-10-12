//
// Created by caohch1 on 10/1/20.
//

#include<iostream>

using namespace std;

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
    return 0;
}