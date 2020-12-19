#include <iostream>

using namespace std;

const int N = 25005;
const int M = 50005;
const int K = 50005;
const int MAX_WEIGHT = 999999999;

/*I need STL !!!*/
struct Pair {
    int first;
    int second;

    explicit Pair(int x = 0, int y = 0) : first(x), second(y) {}

    bool operator>(Pair p) const {
        if (first > p.first) return true;
        else if (first == p.first) {
            if (second > p.second) return true;
        }

        return false;
    }

    bool operator>=(Pair p) const {
        if (first >= p.first) return true;
        return false;
    }
};

inline Pair make_Pair(int x, int y) {
    Pair res(x, y);
    return res;
}

Pair data[M + K];

class Priority_queue {
private:
    int size = 0;

    void MIN_HEAPIFY(int i) {
        if (i == 0) return;

        int l = 2 * i;
        int r = 2 * i + 1;
        int min;
        if (l <= size && data[i] >= data[l]) {
            min = l;
        } else min = i;

        if (r <= size && data[min] >= data[r]) {
            min = r;
        }

        if (min != i) {
            swap(data[i], data[min]);
            MIN_HEAPIFY(min);
        }

    }

    void HEAP_DECREASE_KEY(int i, Pair key) {
        data[i] = key;
        while (i > 1 && data[i / 2] >= data[i]) {
            swap(data[i / 2], data[i]);
            i = i / 2;
        }
    }

public:
    Pair pop() {
        Pair min = data[1];
        data[1] = data[size];
        size--;
        if (size != 0) MIN_HEAPIFY(1);
        return min;
    }

    static Pair top() {
        return data[1];
    }

    void push(Pair key) {
        size++;
        HEAP_DECREASE_KEY(size, key);
    }

    bool empty() const {
        return size == 0;
    };
};

class Queue {
private:
    int data[M + K]{};
    int head = 0;
    int tail = 0;
public:
    void push(int x) {
        data[tail++] = x;
    }

    int pop() {
        return data[head++];
    }

    int front() {
        return data[head];
    }

    bool empty() const {
        return head == tail;
    }
};

struct Node_int {
    int key;
    Node_int *next;

    explicit Node_int(int k, Node_int *n = nullptr) : key(k), next(n) {}
};

class Linked_list_int {
private:
    Node_int *head;
    Node_int *tail;
public:
    Linked_list_int() {
        Node_int *root = new Node_int(0);
        head = root;
        tail = root;
    }

    void push(int x) {
        if (head->key == 0) {
            head->key = x;
            return;
        }
        Node_int *temp = new Node_int(x);

        tail->next = temp;
        tail = temp;

    }

    Node_int *begin() {
        return head;
    }
};

struct Node_pair {
    Pair key;
    Node_pair *next;

    explicit Node_pair(Pair k, Node_pair *n = nullptr) : key(k), next(n) {}
};

class Linked_list_pair {
private:
    Node_pair *head;
    Node_pair *tail;
public:
    Linked_list_pair() {
        Node_pair *root = new Node_pair(make_Pair(-1, -MAX_WEIGHT));
        head = root;
        tail = root;
    }

    void push(Pair x) {
        if (head->key.first == -1) {
            head->key = x;
            return;
        }
        Node_pair *temp = new Node_pair(x);

        tail->next = temp;
        tail = temp;

    }

    Node_pair *begin() {
        return head;
    }
};

Linked_list_pair positive_edges[M];
Linked_list_pair negative_edges[K];
Linked_list_int connected_components[N];

/*main part*/
int in_which_connected_component[N];
int connected_component_deg[N];
bool visited[N];

inline void dfs(int s, int connected_component) {
    if (s == -1) return;

    in_which_connected_component[s] = connected_component;
    connected_components[connected_component].push(s);
    Node_pair *curr = positive_edges[s].begin();
    while (curr != nullptr) {
        if (!in_which_connected_component[curr->key.first]) dfs(curr->key.first, connected_component);
        curr = curr->next;
    }
}

int component_num = 0;

void get_components(int n) {
    for (int i = 1; i <= n; ++i) {
        if (!in_which_connected_component[i]) dfs(i, ++component_num);
    }
}

void get_component_deg(int n) {
    for (int i = 1; i <= n; ++i) {
        Node_pair *curr = negative_edges[i].begin();
        while (curr != nullptr) {
            connected_component_deg[in_which_connected_component[curr->key.first]]++;
            curr = curr->next;
        }
    }
}

int dis[N];

void top_dij(int n, int s) {
    for (int i = 1; i <= n; ++i) {
        dis[i] = MAX_WEIGHT;
        visited[i] = false;
    }
    dis[s] = 0;

    Queue component_queue;

    for (int i = 0; i <= component_num; ++i) {
        if (!connected_component_deg[i]) component_queue.push(i);
    }


    while (!component_queue.empty()) {
        int component_index = component_queue.pop();

        Priority_queue heap; //heap for dij

        Node_int *curr1 = connected_components[component_index].begin();


        while (curr1 != nullptr) {
            if (curr1->key != -1 && dis[curr1->key] < MAX_WEIGHT) {
                heap.push(make_Pair(dis[curr1->key], curr1->key));
            }
            curr1 = curr1->next;
        }

        //main dij
        while (!heap.empty()) {

            Pair temp_edge = heap.pop();

            if (visited[temp_edge.second]) {
                continue;
            } else visited[temp_edge.second] = true;


            Node_pair *curr2 = positive_edges[temp_edge.second].begin();
            while (curr2 != nullptr) {
                if (curr2->key.first != -1 && dis[temp_edge.second] + curr2->key.second < dis[curr2->key.first]) {
                    dis[curr2->key.first] = dis[temp_edge.second] + curr2->key.second;
                    heap.push(make_Pair(dis[curr2->key.first], curr2->key.first));
                }
                curr2 = curr2->next;
            }


            Node_pair *curr3 = negative_edges[temp_edge.second].begin();
            while (curr3 != nullptr) {
                if (dis[temp_edge.second] + curr3->key.second < dis[curr3->key.first]) {
                    dis[curr3->key.first] = dis[temp_edge.second] + curr3->key.second;
                }
                curr3 = curr3->next;
            }
        }

        //judge deg for top_sort
        Node_int *curr4 = connected_components[component_index].begin();
        while (curr4 != nullptr) {
            Node_pair *curr5 = negative_edges[curr4->key].begin();
            while (curr5 != nullptr) {
                if (curr5->key.first != -1 &&
                    !--connected_component_deg[in_which_connected_component[curr5->key.first]]) {
                    component_queue.push(in_which_connected_component[curr5->key.first]);
                }
                curr5 = curr5->next;
            }
            curr4 = curr4->next;
        }
    }
}

int main() {
    int n, m, k, s;
    scanf("%d%d%d%d", &n, &m, &k, &s);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        positive_edges[u].push(make_Pair(v, w));
        positive_edges[v].push(make_Pair(u, w));
    }

    for (int i = 0; i < k; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        negative_edges[u].push(make_Pair(v, w));
    }

    get_components(n);

    get_component_deg(n);

    top_dij(n, s);

    for (int i = 1; i <= n; i++)
        if (dis[i] == MAX_WEIGHT)
            printf("UNREACHABLE\n");
        else
            printf("%d\n", dis[i]);

    return 0;
}