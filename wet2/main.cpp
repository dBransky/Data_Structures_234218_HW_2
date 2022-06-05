#include <iostream>
#include "MyHashTable.h"
#include "MyUnionFind.h"
#include "MyMap.h"

int main() {
    Map<int,int> map;
    map.insert(5,5);
    map.insert(9,5);
    map.insert(1,5);
    map.insert(4,5);
    map.insert(3,5);
    map.insert(20,5);
    map.insert(2,5);
    map.insert(12,5);
    map.insert(15,5);
    map.insert(8,5);
    map.insert(7,5);
    map.insert(40,5);
    map.insert(0,5);
    map.insert(11,5);
    Map<int,int> map2;
    map2.insert(105,5);
    map2.insert(96,5);
    map2.insert(234,5);
    map2.insert(445,5);
    map2.insert(89,5);
    map2.insert(90,5);
    map2.insert(1067,5);
    map2.insert(555,5);
    map2.insert(222,5);
    map2.insert(333,5);
    map2.insert(888,5);
    map2.insert(499,5);
    map.merge(map2);
    return 0;
}
