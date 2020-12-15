//
// Created by MissSirius on 2020/12/15.
//

#include <iostream>

using namespace std;

const int N = 1000;
int servers[N];
__int128 dp[N][N];

inline void print(__int128 x) {
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    int size = 0;
    scanf("%d", &size);

    for (int i = 0; i < size; ++i) {
        scanf("%d", &servers[i]);
    }

    for (int i = 0; i < size - 1; ++i) {
        dp[i][i] = 0;
        dp[i][i + 1] = 0;
    }
    dp[size - 1][size - 1] = 0;

    for (int s = size - 1; s >= 0; --s) {
        for (int e = s + 2; e < size; ++e) {
            __int128 temp = servers[s] + servers[s + 1] + servers[e];
            dp[s][e] = dp[s][s + 1] + dp[s + 1][e] + temp * temp * temp;

            for (int i = s + 2; i < e; ++i) {
                temp = servers[s] + servers[i] + servers[e];
                temp = dp[s][i] + dp[i][e] + temp * temp * temp;
                if (temp < dp[s][e]) dp[s][e] = temp;
//                dp[s][e] = min(dp[s][e], temp);
            }
        }
    }
    print(dp[0][size - 1]);

    return 0;
}