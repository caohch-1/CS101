//
// Created by MissSirius on 2020/11/25.
//

#include <bits/stdc++.h>

using namespace std;
int treeSize = 0;

struct Node {
    int key;
    int height;
    Node *left;
    Node *right;
    int rankCtr;
    int leftCtr;

    explicit Node(int k = -1, int h = 1, Node *l = nullptr, Node *r = nullptr, int d = 0, int lc = 0) : key(k),
                                                                                                        height(h),
                                                                                                        left(l),
                                                                                                        right(r),
                                                                                                        rankCtr(d),
                                                                                                        leftCtr(lc) {};
};

inline int getHeight(Node *node) {
    if (node == nullptr) return 0;
    return node->height;
}

inline Node *rightRotate(Node *node) {
    Node *left = node->left;
    Node *tree = left->right;

    left->right = node;
    node->left = tree;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    left->height = max(getHeight(left->left), getHeight(left->right)) + 1;

    int temp = (tree != nullptr) ? tree->rankCtr : -1;
    node->rankCtr = node->rankCtr - left->rankCtr + temp;
    left->rankCtr = left->rankCtr - temp + node->rankCtr;

    node->leftCtr = (node->left == nullptr) ? 0 : (node->left->rankCtr + 1);
    left->leftCtr = (left->left == nullptr) ? 0 : (left->left->rankCtr + 1);

    return left;
}

inline Node *leftRotate(Node *node) {
    Node *right = node->right;
    Node *tree = right->left;

    right->left = node;
    node->right = tree;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    right->height = max(getHeight(right->left), getHeight(right->right)) + 1;

    int temp = (tree != nullptr) ? tree->rankCtr : -1;
    node->rankCtr = node->rankCtr - right->rankCtr + temp;
    right->rankCtr = right->rankCtr - temp + node->rankCtr;

    node->leftCtr = (node->left == nullptr) ? 0 : (node->left->rankCtr + 1);
    right->leftCtr = (right->left == nullptr) ? 0 : (right->left->rankCtr + 1);

    return right;
}

inline int judgeBalance(Node *node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node *INSERT(Node *node, int key) {
    if (node == nullptr) return (new Node(key));


    if (key < node->key) node->left = INSERT(node->left, key), node->rankCtr++, node->leftCtr++;
    else if (key >= node->key) node->right = INSERT(node->right, key), node->rankCtr++;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = judgeBalance(node);

    if (balance > 1 && key <= node->left->key) return rightRotate(node);
    else if (balance < -1 && key >= node->right->key) return leftRotate(node);
    else if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    } else if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

inline Node *minNode(Node *node) {
    Node *curr = node;
    while (curr->left != nullptr) curr = curr->left;
    return curr;
}

Node *DELETE(Node *pRoot, int key) {
    if (pRoot == nullptr) return pRoot;

    if (key < pRoot->key) pRoot->left = DELETE(pRoot->left, key), pRoot->rankCtr--, pRoot->leftCtr--;
    else if (key > pRoot->key) pRoot->right = DELETE(pRoot->right, key), pRoot->rankCtr--;
    else {
        if (pRoot->left == nullptr || pRoot->right == nullptr) {
            Node *temp = pRoot->left ? pRoot->left : pRoot->right;

            if (temp == nullptr) pRoot = nullptr;
            else *pRoot = *temp, delete temp;
        } else {
            Node *temp = minNode(pRoot->right);
            pRoot->key = temp->key;
            pRoot->right = DELETE(pRoot->right, temp->key);
            pRoot->rankCtr--;
        }
    }

    if (pRoot == nullptr) return pRoot;

    pRoot->height = 1 + max(getHeight(pRoot->left), getHeight(pRoot->right));

    int balance = judgeBalance(pRoot);

    if (balance > 1 && judgeBalance(pRoot->left) >= 0) return rightRotate(pRoot);
    else if (balance > 1 && judgeBalance(pRoot->left) < 0) {
        pRoot->left = leftRotate(pRoot->left);
        return rightRotate(pRoot);
    }
    else if (balance < -1 && judgeBalance(pRoot->right) <= 0) return leftRotate(pRoot);
    else if (balance < -1 && judgeBalance(pRoot->right) > 0) {
        pRoot->right = rightRotate(pRoot->right);
        return leftRotate(pRoot);
    }
    return pRoot;
}

int kTh(Node *pRoot, int k) {
    Node *temp = pRoot;
    int ctr = pRoot->leftCtr;
    while (temp != nullptr) {
        if (k > ctr) {
            if (temp->right != nullptr) ctr += (temp->right->leftCtr + 1);
            temp = temp->right;
        } else if (k < ctr) {
            if (temp->left != nullptr) ctr += (temp->left->leftCtr + 1 - temp->leftCtr - 1);
            temp = temp->left;
        } else if (k == ctr) {
            return temp->key;
        }
    }
    return 114514;
}

int RANK(Node *root, int x) {
    int res = 0;
    while (root != nullptr) {

        int rankCtr = (root->left != nullptr) ? root->left->rankCtr : -1;

        if (root->key >= x) root = root->left;
        else root = root->right, res = res + rankCtr + 2;
    }
    return res;
}

Node *root = nullptr;

struct AVL {
    static void insert(int v) {
        root = INSERT(root, v);
        treeSize++;
    };

    static void remove(int v) {
        root = DELETE(root, v);
        treeSize--;
    };

    static int kth(int k) {
        if (k >= treeSize) {
            Node *temp = root;
            while (temp->right != nullptr) temp = temp->right;
            return temp->key;
        }

        return kTh(root, k);
    };

    static int rank(int v) {
        return RANK(root, v);
    };

    static int size() {
        return treeSize;
    };
};


/* PLEASE DO NOT CHANGE BELOW*/
int A, B, C, lfsr;
double P[4][4];

int lfsr_generator() {
    auto ret = lfsr;
    return (lfsr ^= lfsr << 13, lfsr ^= lfsr >> 17, lfsr ^= lfsr << 5, ret);
}

tuple<int, int> command() {
    auto imm = lfsr_generator();
    static int state = 0;
    auto p = double(lfsr_generator() & 0x7fffffff) / INT32_MAX;
    for (int i = 0; i < 4; i++)
        if ((p -= P[state % 4][i]) < 0) {
            state += 4 - state % 4 + i;
            break;
        }
    return {state % 4, (imm * A + state * B + C) & 0x7fffffff};
}


/* PLEASE DO NOT CHANGE ABOVE*/
int main() {
    int m;
    cin >> m >> lfsr >> A >> B >> C;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) cin >> P[i][j];
    int tans = 0;
    for (int i = 1; i <= m; i++) {
        int op, imm;
        tie(op, imm) = command();
        if (op == 0) AVL::insert(imm);
        if (op == 1) AVL::remove(AVL::kth(imm % AVL::size()));
        if (op == 2) tans ^= AVL::rank(imm);
        if (op == 3) tans ^= AVL::kth(imm % AVL::size());

    }
    cout << tans << "\n";


    return 0;
}