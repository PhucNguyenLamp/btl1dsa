// #include "main.h"

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

    }
    void add(string name, int energy){
        if (size == 0) {
            head = new customer(name, energy, nullptr, nullptr);
            curr = head;
            }
        else if (size == 1){
            head->next = new customer(name, energy, nullptr, nullptr);
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
    void addbefore(customer* cus){

    }
    E remove(){

    }
    E get(){

    }
    int getSize(){

    }
    bool isEmpty(){

    }
    void next(){

    }
    void prev(){

    }
    
}

int main(){


}