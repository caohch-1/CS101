#include <bits/stdc++.h>

clock_t ins = 0, rem = 0, ran = 0, kt = 0;

using namespace std;
const int N = 1000005;

enum COLOR {
    RED, BLACK
};

class NODE {
public:
    int key;
    COLOR color;
    NODE *left;
    NODE *right;
    NODE *parent;

    explicit NODE(int k) : key(k) {
        parent = nullptr, right = nullptr, left = nullptr, color = RED;
    }

    bool isLeftChild() { return this == this->parent->left; }

    bool hasRedChild() const {
        return (this->left != nullptr && this->left->color == RED) ||
               (this->right != nullptr && this->right->color == RED);
    }

    NODE *getUncle() const {
        if (this->parent == nullptr || this->parent->parent == nullptr) return nullptr;

        if (this->parent->isLeftChild()) return this->parent->parent->right;
        else return this->parent->parent->left;
    }

    NODE *getBrother() {
        if (this->parent == nullptr) return nullptr;
        if (this->isLeftChild()) return this->parent->right;

        return this->parent->left;
    }

    void goDown(NODE *pParent) {
        if (this->parent != nullptr) {
            if (this->isLeftChild()) this->parent->left = pParent;
            else this->parent->right = pParent;
        }
        pParent->parent = this->parent;
        this->parent = pParent;
    }
};

class REDBLACKTREE {
public:
    NODE *root;

    NODE *search(int key) const {
        NODE *temp = this->root;

        while (temp != nullptr) {
            if (key < temp->key) {
                if (temp->left == nullptr) break;
                else temp = temp->left;
            } else if (key == temp->key && (temp->right != nullptr && key != temp->right->key)) {
                break;
            } else {
                if (temp->right == nullptr) break;
                else temp = temp->right;
            }
        }

        return temp;
    }

    static NODE *successor(NODE *node) {
        NODE *temp = node;

        while (temp->left != nullptr) temp = temp->left;

        return temp;
    }

    void leftRotate(NODE *node) {
        NODE *parent = node->right;

        if (node == root) root = parent;

        node->goDown(parent);

        node->right = parent->left;

        if (parent->left != nullptr) parent->left->parent = node;

        parent->left = node;
    }

    void rightRotate(NODE *node) {
        NODE *parent = node->left;

        if (node == root) root = parent;

        node->goDown(parent);

        node->left = parent->right;

        if (parent->right != nullptr) parent->right->parent = node;

        parent->right = node;
    }

    void fixRedRed(NODE *node) {
        if (node == root) {
            node->color = BLACK;
            return;
        }

        NODE *parent = node->parent, *grandparent = parent->parent, *uncle = node->getUncle();

        if (parent->color != BLACK) {
            if (uncle != nullptr && uncle->color == RED) {
                parent->color = BLACK;
                grandparent->color = RED;
                uncle->color = BLACK;
                this->fixRedRed(grandparent);
            } else {
                if (parent->isLeftChild()) {
                    if (node->isLeftChild()) swap(parent->color, grandparent->color);
                    else leftRotate(parent), swap(node->color, grandparent->color);

                    rightRotate(grandparent);
                } else {
                    if (node->isLeftChild()) rightRotate(parent), swap(node->color, grandparent->color);
                    else swap(parent->color, grandparent->color);

                    leftRotate(grandparent);
                }
            }
        }
    }

    void fixBlackBlack(NODE *node) {
        if (node == root) return;

        NODE *brother = node->getBrother(), *parent = node->parent;
        if (brother == nullptr) fixBlackBlack(parent);
        else {
            if (brother->color == RED) {
                parent->color = RED;
                brother->color = BLACK;

                if (brother->isLeftChild()) rightRotate(parent);
                else leftRotate(parent);

                fixBlackBlack(node);
            } else {
                if (brother->hasRedChild()) {
                    if (brother->left != nullptr && brother->left->color == RED) {
                        if (brother->isLeftChild())
                            brother->left->color = brother->color, brother->color = parent->color, rightRotate(parent);
                        else brother->left->color = parent->color, rightRotate(brother), leftRotate(parent);
                    } else {
                        if (brother->isLeftChild())
                            brother->right->color = parent->color, leftRotate(brother), rightRotate(parent);
                        else brother->right->color = brother->color, brother->color = parent->color, leftRotate(parent);
                    }
                    parent->color = BLACK;
                } else {
                    brother->color = RED;
                    if (parent->color == BLACK) fixBlackBlack(parent);
                    else parent->color = BLACK;
                }
            }
        }
    }

    static NODE *replace(NODE *node) {
        if (node->left != nullptr && node->right != nullptr) return successor(node->right);

        if (node->left == nullptr && node->right == nullptr) return nullptr;

        if (node->left != nullptr) return node->left;
        else return node->right;
    }

    void insertNode(int key) {
        NODE *newNode = new NODE(key);

        if (this->root == nullptr) newNode->color = BLACK, this->root = newNode;
        else {
            NODE *temp = this->search(key);
            newNode->parent = temp;
            if (key < temp->key) temp->left = newNode;
            else temp->right = newNode;

            this->fixRedRed(newNode);
        }
    }

    void deleteNode(NODE *node) {
        NODE *re = replace(node);

        bool isBlack = ((re == nullptr || re->color == BLACK) && (node->color == BLACK));
        NODE *parent = node->parent;

        if (re == nullptr) {
            if (node == root) root = nullptr;
            else {
                if (isBlack) fixBlackBlack(node);
                else if (node->getBrother() != nullptr) node->getBrother()->color = RED;

                if (node->isLeftChild()) parent->left = nullptr;
                else parent->right = nullptr;
            }
            delete node;
            return;
        }

        if (node->left == nullptr || node->right == nullptr) {
            if (node == root) node->key = re->key, node->left = node->right = nullptr, delete re;
            else {
                if (node->isLeftChild()) parent->left = re;
                else parent->right = re;

                delete node;
                re->parent = parent;
                if (isBlack) fixBlackBlack(re);
                else re->color = BLACK;

            }
            return;
        }

        swap(re->key, node->key);
        deleteNode(re);
    }

    NODE *kTh(NODE *pRoot, int &k) {
        if (pRoot == nullptr) return nullptr;

        NODE *left = kTh(pRoot->left, k);

        if (left != nullptr) return left;

        k--;
        if (k == 0) return pRoot;

        return kTh(pRoot->right, k);
    }

    int rank(int key) {
        stack<NODE *> s;
        NODE *curr = this->root;
        int res = 0;
        while (curr != nullptr || !s.empty()) {
            while (curr != nullptr) s.push(curr), curr = curr->left;
            curr = s.top();
            if (curr->key >= key) return res;
            s.pop(), res++;
            curr = curr->right;
        }
        return res;
    }

    void inorder(NODE *x) {
        if (x == nullptr)
            return;
        inorder(x->left);
        cout << x->key << " ";
        inorder(x->right);
    }
};

REDBLACKTREE RBTree;

struct RB {
    int treeSize = 0;

    void insert(int v) {
        clock_t start = clock();

        RBTree.insertNode(v);
        this->treeSize++;

        clock_t end = clock();
        ins += (end - start);
    };

    void remove(int v) {
        clock_t start = clock();

        if (RBTree.root == nullptr) return;
        NODE *die = RBTree.search(v);

        if (die->key != v) return;

        RBTree.deleteNode(die);
        this->treeSize--;

        clock_t end = clock();
        rem += (end - start);
    };

    int kth(int k) {
        clock_t start = clock();

        int temp = k + 1;
        int res = RBTree.kTh(RBTree.root, temp)->key;

        clock_t end = clock();
        kt += (end - start);
        return res;
    };

    int rank(int v) {
        clock_t start = clock();

        int res = RBTree.rank(v);

        clock_t end = clock();
        ran += (end - start);
        return res;
    };

    int size() {
        return this->treeSize;
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
    RB tree;
    int m;
    cin >> m >> lfsr >> A >> B >> C;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) cin >> P[i][j];
    int tans = 0;
    for (int i = 1; i <= m; i++) {
        int op, imm;
        tie(op, imm) = command();
        if (op == 0) tree.insert(imm);
        if (op == 1) tree.remove(tree.kth(imm % tree.size()));
        if (op == 2) tans ^= tree.rank(imm);
        if (op == 3) tans ^= tree.kth(imm % tree.size());
    }
    cout << tans << "\n";
    cout<<ins * 1.0 / CLOCKS_PER_SEC * 1000 <<" "<<rem * 1.0 / CLOCKS_PER_SEC * 1000 <<" "<<ran * 1.0 / CLOCKS_PER_SEC * 1000<< " "<< kt * 1.0 / CLOCKS_PER_SEC * 1000<<endl;

    return 0;
}

