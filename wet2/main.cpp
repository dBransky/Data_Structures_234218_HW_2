#include <iostream>
#include "MyHashTable.h"
#include "MyUnionFind.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    HashTable* hash = new HashTable();
    UnionFind* UF = new UnionFind(4);
    UF->Itamar(1, 2);
    UF->Itamar(2, 1);
    UF->Itamar(3, 4);
    UF->Itamar(4, 4);
    UF->Union(4,3, 0.75);
    UF->Union(1,4, 0.2);
    UF->Union(1,2, 1);
    UF->PrintStatus();

    return 0;
}
