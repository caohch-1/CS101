//
// Created by caohch1 on 10/3/20.
//
#include <iostream>
//#include <time.h>

using namespace std;
#define MAXLENGTH 1000000
#define HASHCAPACITY 67108864 //2^26
int letterTable[MAXLENGTH][26];
string reStrArr[MAXLENGTH];
//time_t globalStart,globalEnd,hashStart,hashEnd,hashTime=0;;

/*LinkedList for address hash collision */
class LinkedNode {
public:
    LinkedNode(string val) : str(val), next(nullptr) {};
    string str;
    LinkedNode *next;
};

class LinkedList {
private:
    LinkedNode *head;
    LinkedNode *tail;
    int length;
public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {};

    void pushFront(string val) {
        LinkedNode *newNode = new LinkedNode(val);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            LinkedNode *temp = head;
            head = newNode;
            newNode->next = temp;
        }
        length++;
    }

    int getLength() { return length; }

    bool find(string val) {
//        hashStart=clock();

        LinkedNode *curr = head;
        for (int i = 0; i < length; ++i) {
            if (curr->str == val) return true;
            else curr = curr->next;
        }

//        hashEnd=clock();
//        hashTime+=hashEnd-hashStart;
        return false;
    }
};

/*Turn arr[26] into string, actually is rearrange every substring in ascending order*/
string toString(int *arr, int strLength) {
    string res(strLength, ' ');
    int index = 0;
    for (int i = 0; i < 26; ++i) {
        int repeat = arr[i];
        for (int j = 0; j < repeat; ++j) {
            res[index] = 'a' + i;
            index++;
        }
    }
    return res;
}

/*Quicker mod for hash*/
unsigned int hashMod(unsigned int n, unsigned int m){
    return n&(m-1);
}

/*Hash every substring*/
unsigned int hashString(string str) {
    unsigned int hash_value = 0;
    for (int i = 1; i < str.length(); i*=2) {
        hash_value = hashMod(12347 * hash_value + str[i-1],HASHCAPACITY);
    }

    return hash_value;
}

/*Generate random arr*/
string generateRandomArray(int n, int rang) {
    string res(n,' ');
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        res[i] = rand() % rang +'a';
    }
    return res;
}

LinkedList hashTable[HASHCAPACITY];

int main() {
    /*Load data*/
    //Load data from manually input
    int n,k;
    cin>>n>>k;
    string data;
    cin>>data;

//    //Load data from certain testcase
//    int n = 10, k = 1;
//    string data = "ccccababab";

//    //Load data from random generation
//    srand(time(NULL));
//    int n=rand()%(30000);
//    srand(time(NULL));
//    int k=rand()%n;
//    string data= generateRandomArray(n,26);
//    cout<<"n="<<n<<" k="<<k<<endl;

//    globalStart=clock();

    /*Convert each substring into a row in letterTable, using sliding window*/
    //Initialize the first row in letterTable
    for (int i = 0; i < k; ++i) {
        letterTable[0][data[i] - 'a']++;
    }

    //Calculate every sub-string by sliding window
    for (int i = 1; i < n - k + 1; ++i) {
        for (int j = 0; j < 26; ++j) {
            letterTable[i][j] = letterTable[i - 1][j];
        }
        letterTable[i][data[i - 1] - 'a']--;
        letterTable[i][data[i + k - 1] - 'a']++;
    }


    /*Hash Part*/
    //Turn arr[26] in letterTable into string
    for (int i = 0; i < n - k + 1; ++i) {
        reStrArr[i] = toString(letterTable[i], k);
    }

    //Hash
    int res = 0;
    for (int i = 0; i < n - k + 1; ++i) {


        unsigned int hashValue = hashString(reStrArr[i]);


        if (hashTable[hashValue].getLength() == 0) {
            hashTable[hashValue].pushFront(reStrArr[i]);
            res++;
        } else {

            if (hashTable[hashValue].find(reStrArr[i])) continue;
            else{

                hashTable[hashValue].pushFront(reStrArr[i]);
                res++;
            }

        }
    }

    cout<<res<<endl;
//    globalEnd=clock();
//    cout<<"HashTime Consume: "<<1000*hashTime/(double ) CLOCKS_PER_SEC<<" ms"<<endl;
//    cout<<"Time Consume: "<<1000*(globalEnd-globalStart)/(double ) CLOCKS_PER_SEC<<" ms"<<endl;
    return 0;
}

