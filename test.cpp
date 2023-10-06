// #include "main.h"
#include <string>
#include <iostream>
using namespace std;
class customer {
    public:	
        string name;
        int energy;
        customer* prev;
        customer* next;
    public:
        customer(){}
        customer(string na, int e, customer* p, customer *ne): name(na), energy(e), prev(p), next(ne){}
        ~customer(){
            delete prev;
            delete next;
        }
        void print() {
            cout << name << "-" << energy << endl;
        }
    };
class DCLList {
    private:
        customer* head;
        customer* curr;
        int size;
    public:
    DCLList() {
        head = nullptr;
        curr = nullptr;
        size = 0;
    }
    ~DCLList(){
        // delete curr;
    }
    void add(string name, int energy){
        if (size == 0) {
            head = new customer(name, energy, nullptr, nullptr);
            curr = head;
            }
        else if (size == 1){
            head->next = new customer(name, energy, head, head);
            head->prev = head->next;
            curr = head->next;
        } else {
            customer* temp = new customer(name, energy, curr, curr->next);
            curr->next->prev = temp;
            curr->next = temp;
            curr = temp;
        }
        size++;
    }
    void addbefore(string name, int energy){
        if (size == 0) {
            head = new customer(name, energy, nullptr, nullptr);
            curr = head;
            }
        else if (size == 1){
            head->next = new customer(name, energy, nullptr, nullptr);
            head->prev = head->next;
            curr = head->next;
        } else {
            customer* temp = new customer(name, energy, curr->prev, curr);
            curr->prev->next = temp;
            curr->prev = temp;
            curr = temp;
        }
        size++;
    }
    customer* remove(){
        if (size == 0){
            return nullptr;
        }
        if (size == 1){
            customer* temp = curr;
            curr = nullptr;
            head = nullptr;
            size--;
            return temp;
        }
        if (size == 2){
            customer* temp = curr;
            curr = curr->next;
            curr->next = curr;
            curr->prev = curr;
            size--;
            return temp;
        }
        else {
            customer* temp = curr;
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            curr = curr->next;
            size--;
            return temp;
        }
    }
    customer* get(){
        return curr;
    }
    int getSize(){
        return size;
    }
    bool isEmpty(){
        return size == 0;
    }
    void next(){
        curr = curr->next;
    }
    void prev(){
        curr = curr->prev;
    }
    // customer* find(string name){

    // }
};

class LQueue {
    private:
        customer* head;
        customer* curr;
        int size;
    public:
    LQueue() {
        head = nullptr;
        curr = nullptr;
        size = 0;
    }
    ~LQueue(){
        // delete curr;
    }
    void add(string name, int energy){
        if (size==0){
            head = curr = new customer(name, energy, nullptr, nullptr);
        } else {
            curr->next = new customer(name, energy, nullptr, nullptr);
            curr = curr->next;
        }
        size++;
    }
    customer* remove(){
        if (size == 0) return nullptr;
        else if (size == 1){
            customer* temp = head;
            head = curr = nullptr;
            size--;
            return temp;
        } else {
            customer* temp = head;
            head = head->next;
            size--;
            return temp;
        }
    }
    customer* get(){
        return head;
    }
    // void clear(){
        // chưa cần
    // }
    int getSize(){
        return size;
    }
};
int main(){
    // create test cases for queue
    LQueue* q = new LQueue();
    q->add("A", 1);
    q->add("B", 2);
    q->add("C", 3);
    customer* temp = q->remove();
    cout << temp->energy << " " << temp->name;

}