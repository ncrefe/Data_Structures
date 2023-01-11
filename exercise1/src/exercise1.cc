#include "exercise1_utils.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;




// Your heap functions can (but don't have to) be in these forms:
//Node* create_heap(int capacity);
//void push(Node* heap, int size, Node entry);
//Node pop(Node* heap, int size);

class MaxHeap {
    private:
        Node *arr;
        int size;
        int capacity;
        void heapify(int i);
        void heapifyDown(int i);
        void heapifyUp(int i);
    public:
        MaxHeap(int cap) {
            capacity = cap;
            size = 0;
            arr = new Node[cap];
        };
        int getSize() {
            return size;
        };
        int getCapacity() {
            return capacity;
        };
        bool isEmpty() {
            return size == 0;
        };
        bool isFull() {
            return size == capacity;
        };


        void push(Node x);
        Node pop();
        void print();
        void print_k_largest(int k);
};

void MaxHeap::print_k_largest(int k){
    
    if (k > size) {
        cout << "k is larger than the size of the heap" << endl;
        return;
    }

    int i = 0;
    char is_home_char;
    while (i < k) {
        Node max = pop();
        if (max.is_home) {
            is_home_char = 'H';
        } else {
            is_home_char = 'A';
        }

        cout << is_home_char << " " << max.shirt_no << " " << max.score << endl;

        i++;
    }

}

void MaxHeap::heapify(int i) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int largest = i;
    if (left < size && arr[left].score > arr[largest].score) {
        largest = left;
    }
    if (right < size && arr[right].score > arr[largest].score) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(largest);
    }
};

void MaxHeap::heapifyUp(int i) {
    if (i == 0) {
        return;
    }
    int parent = (i - 1) / 2;
    if (arr[parent].score < arr[i].score) {
        swap(arr[parent], arr[i]);
        heapifyUp(parent);
    }

};

void MaxHeap::heapifyDown(int i) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int largest = i;
    if (left < size && arr[left].score > arr[largest].score) {
        largest = left;
    }
    if (right < size && arr[right].score > arr[largest].score) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyDown(largest);
    }
};

void MaxHeap::push(Node x) {
    if (size == capacity) {
        cout << "Heap is full" << endl;
        return;
    }
    size++;
    arr[size - 1] = x;
    heapifyUp(size - 1);
};

Node MaxHeap::pop() {
    if (size == 0) {
        cout << "Heap is empty" << endl;
        return Node();
    }
    Node max = arr[0];
    arr[0] = arr[size - 1];
    size--;
    heapifyDown(0);
    return max;
};

void MaxHeap::print(){
    print_complete_binary_tree(arr, size);
}

vector<string> splitString(string str, char delimiter){
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

int main(int argc, char** argv) {

    string path = argv[1];

    int k = atoi(argv[2]);
    
    int node_capacity = 28;
    MaxHeap heap(node_capacity);

    ifstream file(path);

    string text;
    vector<string> data;
    int score;
    bool is_home; // true if home, false if away
    int shirt_no;

    getline(file, text);

    if (file.is_open()){
        while (getline(file, text) && text != ""){
            data = splitString(text, ',');
            score = atoi(data[2].c_str());
            is_home = data[0] == "H";
            shirt_no = atoi(data[1].c_str());
            Node node;
            node.score = score;
            node.is_home = is_home;
            node.shirt_no = shirt_no;
        
            heap.push(node);
            heap.print();
        }
    }

    heap.print_k_largest(k);




    return 0;
}
