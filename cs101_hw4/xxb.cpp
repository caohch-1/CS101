#include <iostream>
using namespace std;

int variable = 25002;
int parent[25002];
int part[25002];
int into[25002];
int dist[25002];
int visited[25002];

class Heap
{
private:
	int _A[25002][2];
	int size;
	int max_size;
	
public:
    Heap(){
        max_size = 100000;
        size = 0;
		for(int i=0;i<max_size;i++){
			for(int j=0;j<2;j++){
				_A[i][j] = 0;
			}
		}
    }

	void shiftUp(int index){
		int current = index;
		int parent;
		if(index % 2 == 0){parent = current/2 - 1;}
		else{parent = current/2;}
		if(current <=0){return;}
		if(_A[parent][0] > _A[current][0] ||(_A[parent][0] == _A[current][0] && _A[parent][1] > _A[current][1])){
			int temp = _A[parent][0];
			int spy = _A[parent][1];
			_A[parent][0] = _A[current][0];
			_A[parent][1] = _A[current][1];
			_A[current][0] = temp;
			_A[current][1] = spy;
			shiftUp(parent);
		}
	}
	void shiftDown(int index, int end){
		int current = index;
		int left = index*2 + 1;
		if(left > end){return;}
		if((left < end && _A[left][0] > _A[left+1][0]) ||(left < end && _A[left][0] == _A[left+1][0] && _A[left][1] > _A[left+1][1])){left++;}
		if(_A[left][0] < _A[current][0] ||(_A[left][0] == _A[current][0] && _A[left][1] < _A[current][1])){
			int temp = _A[current][0];
			int spy = _A[current][1];
			_A[index][0] = _A[left][0];
			_A[index][1] = _A[left][1];
			_A[left][0] = temp;
			_A[left][1] = spy;
			shiftDown(left, end);
		}
	}
	void push(int element[2])
	{
		_A[size][0] = element[0];
		_A[size][1] = element[1];
		shiftUp(size);
		size++;
	}
	int pop()
	{
		int tmp = _A[0][0];
		int spy = _A[0][1];
		_A[0][0] = _A[size - 1][0];
		_A[0][1] = _A[size - 1][1];
		_A[size - 1][0] = tmp;
		_A[size - 1][1] = spy;
		size--;

		shiftDown(0, size-1);
		return spy;
	}
    int top(){
		return _A[0][0];
	}
	void result(){
		for(int i=0;i<size;i++){
			cout<<"["<<_A[i][0]<<", "<<_A[i][1]<<"] ";
		}
		cout<<endl;
	}
    int heapsize(){
        return size;
    }
};

struct Node{
        int value;
        int index;
        Node *next;
    };

class vertex
{
private:
    
    Node *head;
    Node *pri;
    Node *ptr;
    int value;
    int index;

public:
    bool tag = false;
    vertex(){
        head = NULL;
        value = 0; // value of each node
        index = 0; //index of each node
    }
    void push(int index, int num){
        Node *temp = new Node;
        temp->value = num;
        temp->index = index;
        if(head==NULL){
            temp->next = NULL;
            head = temp;
            pri = temp;
            ptr = head;
        }
        else{
            pri->next = temp;
            temp->next = NULL;
            pri = temp;
        }
        tag = true;
    }
    void pop(){
        if(tag == false)
            return;
        if(head->next == NULL){
            head = NULL;
            tag = false;
        }
        else{
            if(ptr == head){
                head = head->next;
                ptr = head;
            }
            else{
                head = head->next;
            }
        }

    }
    int getvalue(){
        return value;
    }
    Node* first(){
        return head;
    }
    Node* now(){
        return ptr;
    }
    void again(){
        ptr = head;
    }
    void next(){
        ptr = ptr->next;
    }
    bool existORnot(){
        if( ptr == NULL){
            return false;
        }
        else{
            return true;
        }
    }
};


vertex map[25002];
vertex jump[25002];
vertex father[25002]; // as a counter of different part

void set_father(int child, int bin){
    Node *temp;
    parent[child] = bin;
    father[bin].push(child, child);
    temp = map[child].first();
    while(temp != NULL){
        if(parent[temp->index] == 0){
            set_father(temp->index, bin);
        }
        temp = temp->next;
    }
    map[child].again();//reset the ptr
}

vertex topo;
Heap heap;


int main(){
    int n,m,k,s,index,helper,bin_num;
    int x,y,a,b;
    Node *temp,*temp2,*temp3,*same;
    int heap_node[2];
    int heap_top[2];
    scanf("%d%d%d%d", &n, &m, &k, &s);

    for(int i=0;i<25002;i++){
        parent[i] = 0;
        into[i] = 0;//first set of into
        dist[i] = 99999999;//first set of distance
        visited[i] = 0;//first set of visited
    }
    //***************************for each seperated part********************************************//
    for(int i=1;i<=m;i++){
        scanf("%d", &x);
        scanf("%d", &y);
        scanf("%d", &a);
        map[x].push(y, a);
        map[y].push(x, a);
    }
    bin_num = 0;
    for(int i=1;i<=n;i++){
        if(parent[i] == 0){
            bin_num++;
            set_father(i, bin_num);
        }
    }
    dist[s] = 0;
    //*********************************************************************************************//

    //*******************************to link those seperated part**********************************//
    for(int i=1;i<=k;i++){
        scanf("%d", &x);
        scanf("%d", &y);
        scanf("%d", &b);
        jump[x].push(y, b);
    }
    for(int i=1;i<=n;i++){
        if(jump[i].tag == false)
            continue;
        temp = jump[i].first();
        while(temp != NULL){
            into[parent[temp->index]]++;
            temp = temp->next;
        }
    }
    //*********************************************************************************************//

    //***********************Dij and Topo**********************************************************//
    for(int i=1;i<=bin_num;i++){
        if(into[i] == 0){
            topo.push(i,i);
        }
    }
    while(topo.tag != false){
        temp = topo.first(); //the No. of the current bin
        same = father[temp->value].now(); //the <index, index> of the node in the current bin
        while(same != NULL){
            if(dist[same->index] < 99999999){
                heap_node[0] = dist[same->index];
                heap_node[1] = same->index;
                heap.push(heap_node);
            }
            same = same->next;
        }
        while(heap.heapsize() != 0){
            helper = heap.pop();
            heap_top[0] = dist[helper];
            heap_top[1] = helper;
            if(visited[helper] == 1)
                continue;
            visited[helper] = 1;
            
            temp2 = map[helper].first();
            while(temp2 != NULL){
                if(dist[helper] + temp2->value < dist[temp2->index]){
                    dist[temp2->index] = dist[helper] + temp2->value;
                    heap_node[0] = dist[temp2->index];
                    heap_node[1] = temp2->index;
                    heap.push(heap_node);
                }
                temp2 = temp2->next;
            }
            map[helper].again();

            temp2 = jump[helper].first();
            while(temp2 != NULL){
                if(dist[helper] + temp2->value < dist[temp2->index])
                    dist[temp2->index] = dist[helper] + temp2->value;
                temp2 = temp2->next;
            }
        }
        temp2 = father[temp->value].first();
        while(temp2 != NULL){
            temp3 = jump[temp2->value].first();
            while(temp3 != NULL){
                into[parent[temp3->index]] -= 1;
                if(into[parent[temp3->index]] == 0)
                    topo.push(parent[temp3->index], parent[temp3->index]);
                temp3 = temp3->next;
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
        topo.pop();
    }
    for(int i=1;i<=n;i++){
        if(dist[i] == 99999999)
            cout<<"UNREACHABLE"<<endl;
        else{
            cout<<dist[i]<<endl;
        }
    }

    return 0;
}

