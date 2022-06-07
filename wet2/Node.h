//
// Created by Daniel on 4/20/2022.
//


#ifndef DATA_STRUCTURES_234218_NODE_H
#define DATA_STRUCTURES_234218_NODE_H

#include "Pair.h"

template<class T, class Key>
class Node {
public:
    Pair<T, Key> pair;
    Node *left;
    Node *right;
    Node *father;
    int h_left;
    int h_right;
    int balance_factor;
    int rank;
    int sum_grade;

    Node(Node<T, Key> *left, Node<T, Key> *right, Node<T, Key> *father,
         Pair<T, Key> pair);

    void UpdateParams() {
        int rank_left = 0;
        int rank_right = 0;
        int grade_left = 0;
        int grade_right = 0;
        if (this->left == NULL)
            h_left = 0;
        else {
            h_left = std::max(left->h_left, left->h_right) + 1;
            rank_left = left->rank;
            grade_left = left->sum_grade;
        }

        if (this->right == NULL)
            h_right = 0;
        else {
            h_right = std::max(right->h_right, right->h_left) + 1;
            rank_right = right->rank;
            grade_right = right->sum_grade;
        }
        balance_factor = h_left - h_right;
        rank = 1 + rank_right + rank_left;
        sum_grade = grade_right + grade_left + pair.element->grade;
    }
};

template<class T, class Key>
Node<T, Key>::Node(Node<T, Key> *left, Node<T, Key> *right,
                   Node<T, Key> *father, Pair<T, Key> pair):
        pair(pair), left(left), right(right), father(father) {
    h_left = 0;
    h_right = 0;
    balance_factor = 0;
    rank = 1;
    this->UpdateParams();
}


#endif //DATA_STRUCTURES_234218_NODE_H
