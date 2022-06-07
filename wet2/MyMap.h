//
// Created by Daniel on 4/20/2022.
//

#include <memory>
#include "Node.h"


#ifndef DATA_STRUCTURES_234218_Map_H
#define DATA_STRUCTURES_234218_Map_H

template<class T, class Key>
bool CompareKeys(Node<T, Key> *node, Key key) {
    if (node == NULL)
        return false;
    return node->pair.key == key;
}

class MapError : public std::exception {
};

class KeyAlreadyExists : public MapError {
};

class KeyDoesntExist : public MapError {
};


template<class T, class Key>
class Map {
private:
    Node<T, Key> *head;
    int amount;

    Node<T, Key> *GetNode(Node<T, Key> *node, Key key) {
        if (node == NULL)
            return NULL;
        if (CompareKeys(node, key))
            return node;
        if (key < node->pair.key)
            return GetNode(node->left, key);
        if (key > node->pair.key)
            return GetNode(node->right, key);
        return NULL;
    }

    Node<T, Key> *GetLeftestNode(Node<T, Key> *node) {
        if (node == NULL)
            return NULL;
        if (node->left == NULL)
            return node;
        return GetLeftestNode(node->left);
    }

    Node<T, Key> *GetRightestNode(Node<T, Key> *node) {
        if (node->right == NULL)
            return node;
        return GetRightestNode(node->right);
    }

    Node<T, Key> *GetNodeFather(Node<T, Key> *node, Key key) {
        if (node == NULL) {
            return NULL;
        }
        if (CompareKeys(node->left, key))
            return node;
        if (CompareKeys(node->right, key))
            return node;
        if (key < node->pair.key) {
            if (node->left == NULL)
                return node;
            return GetNodeFather(node->left, key);
        }
        if (key > node->pair.key) {
            if (node->right == NULL)
                return node;
            return GetNodeFather(node->right, key);
        }
        return NULL;
    }

    void BalanceRoute(Node<T, Key> *updated_node) {
        while (updated_node != NULL) {
            updated_node->UpdateParams();
            if (updated_node->balance_factor < -1 || updated_node->balance_factor > 1) {
                if (updated_node->balance_factor == 2 && updated_node->left->balance_factor >= 0)
                    LL_Roll(updated_node);
                if (updated_node->balance_factor == 2 && updated_node->left->balance_factor == -1)
                    LR_Roll(updated_node);
                if (updated_node->balance_factor == -2 && updated_node->right->balance_factor == 1)
                    RL_Roll(updated_node);
                if (updated_node->balance_factor == -2 && updated_node->right->balance_factor <= 0)
                    RR_Roll(updated_node);
                break;
            }
            updated_node = updated_node->father;
        }
    }

    void UpdateRouteParams(Node<T, Key> *updated_node) {
        while (updated_node != NULL) {
            updated_node->UpdateParams();
            updated_node = updated_node->father;
        }

    }

    int SumGradesNodes(Node<T, Key> node, int m) {
        if (!node)
            return 0;
        if (m == 0)
            return 0;
        if (node.rank_right < m) {
            return node.grade_right + node.pair.element->grade + SumGradesNodes(node.left, m - node.rank_right - 1);
        }
        if (node.rank_right >= m) {
            return SumGradesNodes(node.right, m);
        }
    }

    bool IsLeftSon(Node<T, Key> *son, Node<T, Key> *father) {
        if (father == NULL || son == NULL)
            return false;
        return father->left == son;
    }

    void LL_Roll(Node<T, Key> *node) {
        Node<T, Key> *temp = node->left;
        Node<T, Key> *father = node->father;
        node->left = temp->right;
        if (node->left != NULL)
            temp->right->father = node;
        temp->right = node;
        node->father = temp;
        if (father == NULL) {
            head = temp;
            head->father = NULL;
        } else {
            if (IsLeftSon(node, father)) {
                father->left = temp;
            } else {
                father->right = temp;
            }
            temp->father = father;
        }
        node->UpdateParams();
        if (temp != NULL)
            temp->UpdateParams();
        if (father != NULL)
            father->UpdateParams();

    }

    void RR_Roll(Node<T, Key> *node) {
        Node<T, Key> *temp = node->right;
        Node<T, Key> *father = node->father;
        node->right = temp->left;
        if (node->right != NULL)
            temp->left->father = node;
        temp->left = node;
        node->father = temp;
        if (father == NULL) {
            head = temp;
            head->father = NULL;
        } else {
            if (IsLeftSon(node, father)) {
                father->left = temp;
            } else {
                father->right = temp;
            }
            temp->father = father;
        }

        node->UpdateParams();
        if (temp != NULL)
            temp->UpdateParams();
        if (father != NULL)
            father->UpdateParams();

    }

    void RL_Roll(Node<T, Key> *node) {
        LL_Roll(node->right);
        RR_Roll(node);


    }

    void LR_Roll(Node<T, Key> *node) {
        RR_Roll(node->left);
        LL_Roll(node);

    }


    Pair<T, Key> *ArrayFromTree() {
        auto *array = new Pair<T, Key>[this->amount];
        int i = 0;
        StoreInorder(this->head, array, &i, this->amount);
        return array;
    }

    Node<T, Key> *
    TreeFromArray(Node<T, Key> *father, Pair<T, Key> *array, int first_index, int last_index) {
        if (first_index > last_index)
            return NULL;
        int mid_index = (first_index + last_index) / 2;
        auto *node =
                new Node<T, Key>(NULL, NULL, father, array[mid_index]);
        node->left = TreeFromArray(node, array, first_index, mid_index - 1);
        node->right = TreeFromArray(node, array, mid_index + 1, last_index);
        node->UpdateParams();
        return node;

    }

    Pair<T, Key> *MergeSortedArrays(Pair<T, Key> array1[], Pair<T, Key> array2[], int array1_size, int array2_size) {
        auto *merged = new Pair<T, Key>[array1_size + array2_size];
        int i = 0;
        int j = 0;
        int new_index = 0;
        while (i < array1_size || j < array2_size) {
            if (j == array2_size && i < array1_size) {
                merged[new_index] = array1[i];
                new_index++;
                i++;
                continue;
            }
            if (i == array1_size && j < array2_size) {
                merged[new_index] = array2[j];
                new_index++;
                j++;
                continue;
            }
            if ((i < array1_size && j < array2_size) && array1[i].key >= array2[j].key) {
                merged[new_index] = array2[j];
                new_index++;
                j++;
                continue;
            }
            if ((i < array1_size && j < array2_size) && array1[i].key < array2[j].key) {
                merged[new_index] = array1[i];
                new_index++;
                i++;
                continue;
            }

        }
        return merged;
    }

    void StoreInorder(Node<T, Key> *node, Pair<T, Key> arr[], int *index, int max, Key *max_key = NULL) {
        if (node == NULL)
            return;
        if (*index == max)
            return;
        StoreInorder(node->left, arr, index, max, max_key);
        if (max_key != NULL) {
            if (node->pair.key > *max_key)
                return;
        }
        if (max > *index) {
            arr[*index] = node->pair;
            (*index)++;
        }
        StoreInorder(node->right, arr, index, max, max_key);

    }

    void FreePostOrder(Node<T, Key> *node) {
        if (node == NULL)
            return;
        FreePostOrder(node->left);
        FreePostOrder(node->right);
        delete (node);
    }

    bool is_valid(Node<T, Key> *node) {
        if (node == NULL)
            return true;
        bool loop_free = (node->father != node) && is_valid(node->left) && is_valid(node->right);
        return loop_free;

    }

    void NULLInorder(Node<T, Key> *node) {
        if (node == NULL)
            return;
        NULLInorder(node->left);
        NULLInorder(node->right);
        node->pair.element = NULL;
    }

    int CountInorder(Node<T, Key> *node, Key *max_key = NULL) {
        if (node == NULL)
            return 0;
        int sum = CountInorder(node->left);
        if (max_key != NULL) {
            if (node->pair.key > *max_key)
                return sum;
        }
        sum++;
        sum += CountInorder(node->right);
        return sum;
    }

    void ArrayByMinMax(Node<T, Key> *node, Pair<T, Key> arr[], int *index, Key min_key, Key max_key) {
        if (node->left != NULL && node->pair.key >= min_key)
            ArrayByMinMax(node->left, arr, index, min_key, max_key);
        if (node->pair.key >= min_key && node->pair.key <= max_key) {
            arr[*index] = node->pair;
            (*index)++;
        }
        if (node->right != NULL && node->pair.key <= max_key)
            ArrayByMinMax(node->right, arr, index, min_key, max_key);

    }

    void CountMinMax(Node<T, Key> *node, int *size, Key min_key, Key max_key) {
        if (node->left != NULL && node->pair.key >= min_key)
            CountMinMax(node->left, size, min_key, max_key);
        if (node->pair.key >= min_key && node->pair.key <= max_key) {
            (*size)++;
        }
        if (node->right != NULL && node->pair.key <= max_key)
            CountMinMax(node->right, size, min_key, max_key);

    }

public:
    Map();

    ~Map();

    bool does_exist(Key key);

    T find(Key key);

    void insert(Key key, T element);

    void remove(Key key);

    void merge(Map &);

    void UpdateGrades(Key key);

    T GetMaxId();

    int GetRank(Key key);

    int SumGrades(int m);

    Pair<T, Key> *GetFirstNum(int NumToReturn);

    Pair<T, Key> *GetObjectsFromKey(Key min_key, Key max_key, int *size);


};

template<class T, class Key>
T Map<T, Key>::find(Key key) {
    Node<T, Key> *result = GetNode(head, key);
    if (result == NULL)
        throw KeyDoesntExist();
    return result->pair.element;
}


template<class T, class Key>
Map<T, Key>::Map() {
    head = NULL;
    amount = 0;
}

template<class T, class Key>
void Map<T, Key>::insert(Key key, T element) {
    if (does_exist(key))
        throw KeyAlreadyExists();
    Node<T, Key> *father = GetNodeFather(head, key);
    if (father != NULL) {
        if ((father->left != NULL && father->left->pair.key == key) ||
            (father->right != NULL && father->right->pair.key == key))
            throw KeyAlreadyExists();
    }
    Pair<T, Key> pair(element, key);
    amount++;
    if (father == NULL) {
        head = new Node<T, Key>(NULL, NULL, NULL, pair);
        return;
    }
    if (father->pair.key > key) {
        if (father->left == NULL) {
            father->left = new Node<T, Key>(NULL, NULL, father, pair);
            father->UpdateParams();
        } else {
            father->left->pair.element = element;
        }
        BalanceRoute(father->left);
    } else {
        if (father->right == NULL) {
            father->right = new Node<T, Key>(NULL, NULL, father, pair);
        } else {
            father->right->pair.element = element;
        }
        BalanceRoute(father->right);
    }
}

template<class T, class Key>
void Map<T, Key>::remove(Key key) {
    Node<T, Key> *node = GetNode(head, key);
    if (node == NULL)
        throw KeyDoesntExist();
    Node<T, Key> *temp = NULL;
    amount--;
    if (amount == 0) {
        delete head;
        head = NULL;
        return;
    }
    if (node->right != NULL && node->left != NULL) {
        Node<T, Key> *leftest = GetLeftestNode(node->right);
        if (leftest == node->right) {
            leftest->left = node->left;
            temp = leftest;
            temp->father = node->father;
            if (leftest->left != NULL)
                leftest->left->father = leftest;
        } else {
            temp = leftest->father;
            temp->left = leftest->right;
            if (leftest->right != NULL)
                leftest->right->father = temp;
            leftest->father = NULL;
            leftest->left = node->left;
            if (leftest->left != NULL)
                leftest->left->father = leftest;
            leftest->right = node->right;
            if (leftest->right != NULL)
                leftest->right->father = leftest;
        }
        if (node->father == NULL) {
            head = leftest;
        } else {
            if (IsLeftSon(node, node->father))
                node->father->left = leftest;
            else
                node->father->right = leftest;
            leftest->father = node->father;
        }
        temp->UpdateParams();
        leftest->UpdateParams();
        node->pair.element = NULL;
        delete (node);
        BalanceRoute(temp);
        return;
    }
    if (node->right == NULL && node->left == NULL) {
        temp = node->father;
        if (node->father == NULL) {
            head = temp;
        } else {
            if (IsLeftSon(node, node->father))
                node->father->left = NULL;
            else
                node->father->right = NULL;
        }
    } else {
        if (node->right == NULL)
            temp = node->left;
        if (node->left == NULL)
            temp = node->right;
        if (node->father == NULL) {
            head = temp;
            temp->father = NULL;
        } else {
            if (IsLeftSon(node, node->father)) {
                {
                    node->father->left = temp;
                    temp->father = node->father;
                }
            } else {
                node->father->right = temp;
                temp->father = node->father;
            }
        }
    }
    temp->UpdateParams();
    node->pair.element = NULL;
    delete (node);
    BalanceRoute(temp);
}

template<class T, class Key>
T Map<T, Key>::GetMaxId() {
    if (head == NULL) {
        return NULL;
    }
    auto *node = GetRightestNode(head)->pair.element;
    return node;
}


template<class T, class Key>
Pair<T, Key> *Map<T, Key>::GetFirstNum(int NumToReturn) {
    if (NumToReturn == 0)
        return NULL;
    auto *array = new Pair<T, Key>[NumToReturn];
    int i = 0;
    StoreInorder(this->head, array, &i, NumToReturn);
    return array;
}

template<class T, class Key>
Pair<T, Key> *Map<T, Key>::GetObjectsFromKey(Key min_key, Key max_key, int *size) {
    *size = 0;
    if (head == NULL) {
        *size = 0;
        return NULL;
    }
    CountMinMax(head, size, min_key, max_key);
    auto *array = new Pair<T, Key>[*size];
    int i = 0;
    ArrayByMinMax(head, array, &i, min_key, max_key);
    return array;

}

template<class T, class Key>
Map<T, Key>::~Map() {
    FreePostOrder(head);
}

template<class T, class Key>
void Map<T, Key>::merge(Map &map) {
    Pair<T, Key> *array1 = map.ArrayFromTree();
    Pair<T, Key> *array2 = this->ArrayFromTree();
    Pair<T, Key> *merged = MergeSortedArrays(array1, array2, map.amount, this->amount);
    amount = map.amount + this->amount;
    NULLInorder(map.head);
    NULLInorder(this->head);
    FreePostOrder(head);
    head = TreeFromArray(NULL, merged, 0, amount - 1);
    for (int i = 0; i < map.amount; ++i) {
        array1[i].element = NULL;
    }
    for (int i = 0; i < this->amount - map.amount; ++i) {
        array2[i].element = NULL;
    }
    delete[] array1;
    delete[] array2;
    for (int i = 0; i < amount; ++i) {
        merged[i].element = NULL;
    }
    delete[] merged;

}

template<class T, class Key>
bool Map<T, Key>::does_exist(Key key) {
    Node<T, Key> *result = GetNode(head, key);
    return result;
}

template<class T, class Key>
int Map<T, Key>::GetRank(Key key) {
    Node<T, Key> *result = GetNode(head, key);
    if (result == NULL)
        throw KeyDoesntExist();
    return result->rank;
}

template<class T, class Key>
void Map<T, Key>::UpdateGrades(Key key) {
    Node<T, Key> *result = GetNode(head, key);
    if (result == NULL)
        throw KeyDoesntExist();
    UpdateRouteParams(result);
}

template<class T, class Key>
int Map<T, Key>::SumGrades(int m) {
    return SumGradesNodes(head, m);
}


#endif //DATA_STRUCTURES_234218_Map_H
