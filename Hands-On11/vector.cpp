#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data;      
    int size;       
    int capacity;   

    void resize(int new_capacity) {
        int* new_data = new int[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    DynamicArray() {
        size = 0;
        capacity = 1;
        data = new int[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data; 

            size = other.size;
            capacity = other.capacity;
            data = new int[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push_back(int value) {
        if (size == capacity) {
            resize(2 * capacity); 
        }
        data[size++] = value;
    }

    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    int& operator[](int index) {
        if (index >= 0 && index < size) {
            return data[index];
        } else {
            cout << "Index out of bounds\n";
            return data[0];
        }
    }

    int getSize() const {
        return size;
    }

    void clear() {
        size = 0;
    }
};

int main() {
    DynamicArray arr;
    arr.push_back(5);
    arr.push_back(10);
    arr.push_back(15);

    cout << "Array elements:\n";
    for (int i = 0; i < arr.getSize(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    arr.pop_back();
    cout << "After pop_back:\n";
    for (int i = 0; i < arr.getSize(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
