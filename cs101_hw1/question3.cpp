//
// Created by caohch1 on 10/3/20.
//
#include <iostream>

using namespace std;

/*Initialization*/
const int N = 1000005;
int dataArr[N][26];
struct subStr {
    int arr[26];
} letterTable[N];

//Judge whether 2 arr are same
bool equ(const int *arr1,const int *arr2) {
    for (int i = 0; i < 26; ++i) {
        if (arr1[i] != arr2[i]) return false;
    }
    return true;
}

//Judge relation between two arr
bool inv(const int *arr1,const int *arr2) {
    for (int i = 0; i < 26; ++i) {
        if (arr1[i] != arr2[i]) return arr1[i] < arr2[i];
    }
    return true;
}

//Quick Sort for 2D arr
int PARTITION(subStr *arr, int l, int r) {
    subStr pivot = arr[l];
    int i = l + 1, j = r;
    while (true) {
        while (inv(arr[i].arr, pivot.arr) && i <= r)i++;
        while (j >= l + 1 && inv(pivot.arr, arr[j].arr))j--;

        if (i > j)break;
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    swap(arr[l], arr[j]);

    return j;
}

void QUICKSORT(subStr *arr, int l, int r) {
    if (l >= r) return;

    int p = PARTITION(arr, l, r);
    QUICKSORT(arr, l, p - 1);
    QUICKSORT(arr, p + 1, r);

}

int main() {
    /*Load data*/

    //Load data from manually input
    int n, k;
    cin >> n >> k;
    char data[n + 10];
    scanf("%s", data + 1);


    /*Turn subStr into arr[26]*/
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= 25; ++j) {
            dataArr[i][j] = dataArr[i - 1][j];
        }
        dataArr[i][data[i] - 'a']++;
    }

    int cnt = 0;
    for (int i = k; i <= n; ++i) {
        for (int j = 0; j <= 25; ++j) {
            letterTable[cnt].arr[j] = dataArr[i][j] - dataArr[i - k][j];
        }
        cnt++;
    }


    /*KeyPoint: Sort arrays*/
    //make same subStr get together by sorting
    QUICKSORT(letterTable, 0, n - k);


    /*Calculate res*/
    int final = 1;
    for (int i = 1; i < n - k + 1; ++i) {
        //if prev != curr, different subStr appears
        if (!equ(letterTable[i].arr, letterTable[i - 1].arr)) final++;
    }

    /*Bingo!*/
    cout << final << endl;
    return 0;
}