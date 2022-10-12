#include "structure.h"

int main(int argc, char** argv) {
    tree<int>* t = new tree<int>();\
    t->insert(3);
    t->insert(2);
    t->insert(4);
    t->insert(5);
    t->insert(6);
    t->insert(8);
    t->insert(7);
    t->print();
    delete t;
    return 0;
}