//
// Created by Daniel on 4/22/2022.
//

#ifndef DATA_STRUCTURES_234218_PAIR_H
#define DATA_STRUCTURES_234218_PAIR_H

template<class T, class Key>
class Pair {
public:
    T element;
    Key key;
    Pair(){
    };
    Pair(T element, Key key) : element(element), key(key) {};
};

#endif //DATA_STRUCTURES_234218_PAIR_H
