#include <iostream>

using namespace std;
const int N = 500005;
int m, n;
int res = 0;
bool exists = true;

struct node {
    int index;
    int cost;
    node *next;

    explicit node(int i = -1, int c = 0, node *ne = nullptr) : index(i), cost(c), next(ne) {};
};

class linkedList {
public:
    node *root = nullptr;
    node *curr = nullptr;

    void addNode(node *newNode) {
        if (root == nullptr) {
            root = newNode;
            curr = root;
        } else {
            curr->next = newNode;
            curr = curr->next;
        }
    }
};

linkedList graph[N];

int dfs(int i, int l) {
    int maxNeed = 0;
    bool ampHere = false;
    node *ptr = graph[i].root;
    if (ptr->next == nullptr) return 1;

    while (ptr) {
        if (ptr->index != l) {
            if (ptr->cost >= m) exists = false;
            int need = 0;
            if (ptr->index != l) {
                need += (dfs(ptr->index, i) + ptr->cost);
            }

            if (need == m && !ampHere && i != 1) {
                ampHere = true;
                res++;
            } else if (need > m) {
                res++;
                need = 1 + ptr->cost;
            }
            maxNeed = max(maxNeed, need);
        }
        ptr = ptr->next;
    }

    return ampHere ? 1 : maxNeed;
}


int main() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int index1, index2, cost;
        cin >> index1;
        cin >> index2;
        cin >> cost;
        node *node1 = new node(index1, cost);
        node *node2 = new node(index2, cost);
        graph[index1].addNode(node2);
        graph[index2].addNode(node1);
    }
    cin >> m;

    dfs(1, 0);
    if (exists) cout << res;
    else cout << "No solution.";
    return 0;
}
