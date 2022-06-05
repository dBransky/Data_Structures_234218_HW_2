#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "EmployeeManager.h"
#include <iostream>

class MyNode
{
private:
    Employee* value;
    MyNode* next;

public:
    MyNode(Employee* employee, MyNode* next = NULL) : value(employee), next(next) {};
    Employee* GetValue() { return value; }
    MyNode* GetNext() { return next; }
    void SetNext(MyNode* newNext) { next = newNext; }
};

class MyList
{
private:
    MyNode* head;
public:
    MyList() { head = NULL; }
    ~MyList()
    {
        MyNode* ptr = head;
        MyNode* temp = ptr;
        while (ptr != NULL)
        {
            delete(ptr->GetValue());
            ptr = ptr->GetNext();
            delete(temp);
            temp = ptr;
        }
    }

    void InsertAtBeginning(Employee* newEmployee)
    {
        head = new MyNode(newEmployee, head);
    }
    void DeleteFromList(int id)
    {
        if (head->GetValue()->GetEmployeeId() == id)
        {
            MyNode* temp = head;
            head = head->GetNext();
            delete(temp->GetValue());
            temp->SetNext(NULL);
            delete(temp);
        }
        else
        {
            MyNode* ptr = head;
            MyNode* temp = ptr;
            bool found = false;
            while (ptr->GetNext() != NULL && !found)
            {
                if (ptr->GetNext()->GetValue()->GetEmployeeId() == id)
                {
                    temp = ptr->GetNext();
                    ptr->SetNext(ptr->GetNext()->GetNext());
                    delete(temp->GetValue());
                    temp->SetNext(NULL);
                    delete(temp);
                    found = true;
                }
                else
                {
                    ptr = ptr->GetNext();
                }
            }
        }
    }
    bool IsExist(int id) const
    {
        MyNode *ptr = head;
        while (ptr != NULL)
        {
            if (ptr->GetValue()->GetEmployeeId() == id)
            {
                return true;
            }
            ptr = ptr->GetNext();
        }
        return false;
    }
    Employee* FindInlist(int id) const
    {
        MyNode *ptr = head;
        while (ptr != NULL)
        {
            if (ptr->GetValue()->GetEmployeeId() == id)
            {
                return ptr->GetValue();
            }
            ptr = ptr->GetNext();
        }
        return NULL;
    }
    MyNode* GetFirstNode() const { if (head == NULL) { return NULL; } else return head; }

    void PrintList()
    {
        MyNode* ptr = head;
        if (ptr != NULL) {
            while (ptr->GetNext() != NULL) {
                std::cout << ptr->GetValue()->GetEmployeeId() << "->";
                ptr = ptr->GetNext();
            }
            std::cout << ptr->GetValue()->GetEmployeeId() << std::endl;
        }
    }
};

class HashTable
{
private:
    MyList** employees;
    int arraySize;
    int currentAmount;

    static const int load_factor = 4;
    static const int expand_factor = 2;
    static const int starting_length = 2;

public:
    HashTable()
    {
        employees = new MyList*[starting_length];
        for (int i = 0; i < starting_length; i++)
        {
            employees[i] = new MyList();
        }
        arraySize = starting_length;
        currentAmount = 0;
    }

    int GetHashKey(int id) const
    {
        return id % arraySize;
    }

    void ExpandSize()
    {
        MyList** new_array = new MyList*[arraySize * expand_factor];
        for (int i = 0; i < arraySize * expand_factor; i++)
        {
            new_array[i] = new MyList();
        }
        int original_size = arraySize;
        MyList** temp = employees;
        employees = new_array;
        arraySize = arraySize * expand_factor;
        MyNode* ptr;
        for (int i = 0; i < original_size ; i++)
        {
            if (temp[i]->GetFirstNode() != NULL) {
                ptr = temp[i]->GetFirstNode();
                while (ptr != NULL) {
                    Insert(ptr->GetValue());
                    ptr = ptr->GetNext();
                }
            }
        }
        delete temp;
    }

    void ReduceSize()
    {
        MyList** new_array = new MyList*[arraySize / expand_factor];
        for (int i = 0; i < arraySize / expand_factor; i++)
        {
            new_array[i] = new MyList();
        }
        int original_size = arraySize;
        MyList** temp = employees;
        employees = new_array;
        arraySize = arraySize / expand_factor;
        MyNode* ptr;
        for (int i = 0; i < original_size ; i++)
        {
            if (temp[i] != NULL) {
                if (temp[i]->GetFirstNode() != NULL) {
                    ptr = temp[i]->GetFirstNode();
                    while (ptr != NULL) {
                        Insert(ptr->GetValue());
                        ptr = ptr->GetNext();
                    }
                }
            }
        }
        delete temp;
    }

    void Insert(Employee* employee)
    {
        if (currentAmount >= load_factor * arraySize)
        {
            ExpandSize();
        }
        int key = GetHashKey(employee->GetEmployeeId());
        employees[key]->InsertAtBeginning(employee);
        currentAmount++;
    }

    bool DeleteById(int id)
    {
        int key = GetHashKey(id);
        bool exist = employees[key]->IsExist(id);
        if (exist)
        {
            employees[key]->DeleteFromList(id);
            currentAmount--;
            if (currentAmount / load_factor <= arraySize && arraySize >= starting_length)
            {
                ReduceSize();
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    void DeleteByEmployee(Employee* employee)
    {
        DeleteById(employee->GetEmployeeId());
    }

    Employee* FindById(int id)
    {
        int index = GetHashKey(id);
        return employees[index]->FindInlist(id);
    }

    void PrintHash()
    {
        for (int i = 0; i < arraySize; i++)
        {
            employees[i]->PrintList();
        }
    }
};

#endif