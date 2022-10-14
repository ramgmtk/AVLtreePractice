#include <iostream>
#include <chrono>

#include "structure.h"

#define I_MAX 2147483647 / 1000
#define I_MIN -2147483648 / 1000

int main(int argc, char** argv) {
    tree<int>* t = new tree<int>();
    queue<int>* q = new queue<int>();

    //populate tree
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Populating a tree with values." << std::endl;
    for (int i = I_MIN; i <= I_MAX; i++) t->insert(i);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    double time = duration.count() / 1000000000.0;
    std::cout << "Time to populate tree: " << time << " seconds." << std::endl;
    
    //populate list
    start = std::chrono::high_resolution_clock::now();
    std::cout << "Populating a list with values." << std::endl;
    for (int i = I_MIN; i <= I_MAX; i++) q->list_insert(i);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    time = duration.count() / 1000000000.0;
    std::cout << "Time to populate list: " << time << " seconds." << std::endl;

    int to_find = rand()%(I_MAX - I_MIN + 1) + I_MIN;

    //find value in list
    start = std::chrono::high_resolution_clock::now();
    std::cout << "Finding value in list" << std::endl;
    q->find(to_find);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    time = duration.count() / 1000000000.0;
    std::cout << "Time to find value in list: " << time << " seconds." << std::endl;

    //find value in tree
    start = std::chrono::high_resolution_clock::now();
    std::cout << "Finding value in tree" << std::endl;
    t->find(to_find);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    time = duration.count() / 1000000000.0;
    std::cout << "Time to find value in tree: " << time << " seconds." << std::endl;

    delete q;
    delete t;
    return 0;
}