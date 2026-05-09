#pragma once
#pragma once
#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
using namespace std;

template <class T>
class Storage {
private:
    T data[100];
    int count;

public:
    // Constructor
    Storage() {
        count = 0;
    }

    // Destructor
    ~Storage() {
        count = 0;
    }

    // Add a new object to storage
    void add(const T& item) {
        if (count < 100) {
            data[count] = item;
            count++;
        }
        else {
            cout << "Storage is full!" << endl;
        }
    }

    // Remove object by ID
    void removeById(int id) {
        for (int i = 0; i < count; i++) {
            if (data[i].getId() == id) {
                // Shift all elements left
                for (int j = i; j < count - 1; j++) {
                    data[j] = data[j + 1];
                }
                count--;
                return;
            }
        }
        cout << "Record not found with ID: " << id << endl;
    }

    // Find object by ID - returns pointer or nullptr
    T* findById(int id) {
        for (int i = 0; i < count; i++) {
            if (data[i].getId() == id) {
                return &data[i];
            }
        }
        return nullptr;
    }

    // Get all objects - returns pointer to array
    T* getAll() {
        return data;
    }

    // Get current count
    int size() const {
        return count;
    }

    // Check if storage is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Clear all records
    void clear() {
        count = 0;
    }
};

#endif
