#include <iostream>
class test {
    public:
        class inside{
            public:
                int energy;
                inside* prev;
                inside* next;
        };
    test() {
        head = new inside();
        tail = new inside();
        head->energy = 1;
        tail->energy = 2;
        head->next = tail;
        tail->prev = head;
        head->prev = tail;
        tail->next = head;
    };
    inside *head;
    inside *tail;
    void print(){
        std::cout << head->energy << std::endl;
        std::cout << tail->energy << std::endl;
    }
};
int main(){
    test* t = new test();
    t->print();
    return 0;
}