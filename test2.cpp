#include <iostream>

class Array {
private:
    int* data;
    size_t size;

public:
    Array(size_t size) : size(size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = i;
        }
    }

    int operator+(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    // Destructor to clean up the dynamically allocated memory
    ~Array() {
        delete[] data;
    }
};

int main() {
    Array arr(10);

    // Now you can use the overloaded + operator to access array elements
    std::cout << arr+9 << std::endl; // Prints the element at index 5

    return 0;
}