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
    int rank_left;
    int rank_right;
    int rank;
    long long sum_grade;
    long long grade_left;
    long long grade_right;
    long long bonus_right;
    long long bonus_left;

    Node(Node<T, Key> *left, Node<T, Key> *right, Node<T, Key> *father,
         Pair<T, Key> pair, bool isCompany);

    void UpdateParams(bool isCompany) {
        if (this->left == NULL) {
            h_left = 0;
            rank_left = 0;
            grade_left = 0;
        } else {
            h_left = std::max(left->h_left, left->h_right) + 1;
            rank_left = left->rank;
            grade_left = left->sum_grade+rank_left*bonus_left;
        }

        if (this->right == NULL) {
            h_right = 0;
            rank_right = 0;
            grade_right = 0;
        } else {
            h_right = std::max(right->h_right, right->h_left) + 1;
            rank_right = right->rank;
            grade_right = right->sum_grade+rank_right*bonus_right;
        }
        balance_factor = h_left - h_right;
        rank = 1 + rank_right + rank_left;
        if (rank_left==0)
            bonus_left=0;
        if (rank_right==0)
            bonus_right=0;

        if (isCompany)
        {
                sum_grade = grade_right + grade_left + pair.element->GetGradeValueInCompany();
        }
        else
        {
                sum_grade = grade_right + grade_left + pair.element->GetGradeValueInAllEmployees();
        }

    }
};

template<class T, class Key>
Node<T, Key>::Node(Node<T, Key> *left, Node<T, Key> *right,
                   Node<T, Key> *father, Pair<T, Key> pair, bool isCompany):
        pair(pair), left(left), right(right), father(father) {
    h_left = 0;
    h_right = 0;
    balance_factor = 0;
    rank = 1;
    bonus_left=0;
    bonus_right=0;
    this->UpdateParams(isCompany);
}


#endif //DATA_STRUCTURES_234218_NODE_H
