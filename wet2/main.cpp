#include <iostream>
#include "MyHashTable.h"
#include "MyUnionFind.h"
#include "MyMap.h"

int main() {
    UnionFind* u = new UnionFind(4);
    u->Itamar(1,2);
    u->Itamar(2,1);
    u->Itamar(3,4);
    u->Itamar(4,4);

    u->PrintStatus();

    u->Union(4,3,0.75);
    u->Union(1,4,0.2);
    u->Union(1,2,1);
    u->PrintStatus();

    return 0;
}
