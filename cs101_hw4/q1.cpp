#include <iostream>

using namespace std;
const int MAX_WEIGHT = 20000;


void floyd_warshall(int** dis_matrix, int V_num) {
    for (int k = 1; k <= V_num; ++k) {
        for (int i = 1; i <= V_num; ++i) {
            for (int j = 1; j <= V_num; ++j) {
                if (dis_matrix[i][k] != MAX_WEIGHT && dis_matrix[k][j] != MAX_WEIGHT &&
                    dis_matrix[i][k] + dis_matrix[k][j] < dis_matrix[i][j])
                    dis_matrix[i][j] = dis_matrix[i][k] + dis_matrix[k][j];
            }
        }
    }
}


int main() {
    int n, m, k, s;
    scanf("%d%d%d%d", &n, &m, &k, &s);
    int** dis_matrix = new int* [n + 1];
    for (int i = 0; i < n + 1; ++i) {
        dis_matrix[i] = new int [n+1];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dis_matrix[i][j] = MAX_WEIGHT;
        }
    }
    for (int i = 1; i <= n; ++i) {
        dis_matrix[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int p1, p2, w;
        scanf("%d%d%d", &p1, &p2, &w);
        dis_matrix[p1][p2] = w;
    }

    for (int i = 0; i < k; ++i) {
        int p1, p2, w;
        scanf("%d%d%d", &p1, &p2, &w);
        dis_matrix[p1][p2] = w;
        dis_matrix[p2][p1] = w;
    }


    floyd_warshall(dis_matrix, n);

//    for (int i = 1; i <= test.V_num; ++i) {
//        for (int j = 1; j <= test.V_num; ++j) {
//            cout << dis_matrix[i][j] << " ";
//        }
//        cout << endl;
//    }

    for (int i = 1; i <= n; ++i) {
        if (dis_matrix[s][i] == MAX_WEIGHT) printf("UNREACHABLE\n");
        else printf("%d\n", dis_matrix[s][i]);
    }

    return 0;
}