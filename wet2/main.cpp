#include <iostream>
#include "MyHashTable.h"
#include "MyUnionFind.h"
#include "HighTech.h"
#include "MyMap.h"

int main() {
    UnionFind* u = new UnionFind(4);
    HighTech* h = new HighTech(4);

    u->PrintStatus();

    u->PrintStatus();
    double x = 200000000.0;
    std::cout << x << std::endl;
    int value = (int)(x * 10 + 1e-4);
    std::cout << "CompanyValue: " << value / 10 << "." << (value % 10) << std::endl;
    return 0;
}
