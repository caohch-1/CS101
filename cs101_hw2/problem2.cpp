#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1000005;
typedef long long ll;
int num;

struct myPair {
    ll price;
    ll cost;

    myPair(ll i = 0, ll b = 0) : price(i), cost(b) {};
} data[N];

myPair point;

myPair add(myPair x, myPair y) {
    ll x0 = x.price, x1 = x.cost;
    ll y0 = y.price, y1 = y.cost;
    return myPair(x0 + y0, x1 + y1);
}

myPair sub(myPair x, myPair y) {
    ll x0 = x.price, x1 = x.cost;
    ll y0 = y.price, y1 = y.cost;
    return myPair(x0 - y0, x1 - y1);
}

bool larger(myPair x, myPair y) {
    if (x.price > y.price) return true;
    else if (x.price < y.price) return false;
    else if (x.price == y.price) {
        if (x.cost > y.cost) return true;
        else if (x.cost < y.cost) return false;
        else if (x.cost == y.cost) return false;
    }
    return false;
}

bool largerE(myPair x, myPair y) {
    if (x.price > y.price) return true;
    else if (x.price < y.price) return false;
    else if (x.price == y.price) {
        if (x.cost > y.cost) return true;
        else if (x.cost < y.cost) return false;
        else if (x.cost == y.cost) return true;
    }
    return false;
}

class pQueue {
public:
    myPair cards[N];
    int size = 0;

    bool empty() const { return size == 0; }
} queue;

void MIN_HEAPIFY(pQueue &arr, int i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int min;
    if (l <= arr.size && largerE(arr.cards[i], arr.cards[l])) {
        min = l;
    } else min = i;

    if (r <= arr.size && largerE(arr.cards[min], arr.cards[r])) {
        min = r;
    }

    if (min != i) {
        swap(arr.cards[i], arr.cards[min]);
        MIN_HEAPIFY(arr, min);
    }
}

ll HEAP_EXTRACT_MIN(pQueue &arr) {
    ll min = arr.cards[1].price;
    arr.cards[1] = arr.cards[arr.size];
    arr.size--;
    MIN_HEAPIFY(arr, 1);
    return min;
}

void HEAP_DECREASE_KEY(pQueue &arr, int i, myPair key) {
    arr.cards[i] = key;
    while (i > 1 && largerE(arr.cards[i / 2], arr.cards[i])) {
        swap(arr.cards[i], arr.cards[i / 2]);
        i = i / 2;
    }
}

void MIN_HEAP_INSERT(pQueue &arr, myPair key) {
    arr.size++;
    HEAP_DECREASE_KEY(arr, arr.size, key);
}

void calculate(myPair *sample, int n) {
    for (int i = 0; i < n; ++i) {
        myPair price(sample[i].price, 0);
        if (!queue.empty() and larger(sample[i], queue.cards[1])) {
            point = add(point, sub(price, queue.cards[1]));
            HEAP_EXTRACT_MIN(queue);
            MIN_HEAP_INSERT(queue, price);
        }
        MIN_HEAP_INSERT(queue, myPair(sample[i].price, 1));
    }
}


int main() {
    cin >> num;
    for (int i = 0; i < num; ++i) {
        cin >> data[i].price;
    }
    calculate(data, num);

    cout << point.price << " " << -(2 * point.cost) << endl;

    return 0;
}