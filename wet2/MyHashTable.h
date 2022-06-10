#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "EmployeeManager.h"
#include <iostream>

static int itamar_check = 0;

class MyNode
{
private:
    Employee* value;
    MyNode* next;

public:
    MyNode(Employee* employee, MyNode* next = NULL) : value(employee), next(next) {};
    Employee* GetValue() { return value; }
    void SetValueToNull() { value = NULL; }
    MyNode* GetNext() { return next; }
    void SetNext(MyNode* newNext) { next = newNext; }
};

class MyList
{
private:
    MyNode* head;
public:
    MyList()
    {
        head = NULL;
    }
    int DeleteAllList()
    {
        int total = 0;
        MyNode* ptr = head;
        MyNode* temp = ptr;
        while (ptr != NULL)
        {
           delete ptr->GetValue();
            itamar_check--;
           ptr = ptr->GetNext();
           delete temp;
           itamar_check--;
           temp = ptr;
           total++;
        }
        head = NULL;
        return total;
    }
    ~MyList()
    {
    }

    void InsertAtBeginning(Employee* newEmployee)
    {
        head = new MyNode(newEmployee, head);
        itamar_check += 2;
    }
    void DeleteFromList(int id)
    {
        if (head->GetValue()->GetEmployeeId() == id)
        {
            MyNode* temp = head;
            head = head->GetNext();
            delete(temp->GetValue());
            itamar_check--;
            temp->SetNext(NULL);
            delete(temp);
            itamar_check--;
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
                    itamar_check--;
                    temp->SetNext(NULL);
                    delete(temp);
                    itamar_check--;
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

    bool ListIsValid()
    {
        MyNode* ptr = head;
        while (ptr != NULL)
        {
            if (ptr->GetValue() == NULL)
            {
                return false;
            }
            ptr = ptr->GetNext();
        }
        return true;
    }
};

class HashTable
{
private:
    MyList** employees;
    int arraySize;
    int currentAmount;


    static const int free_factor = 3;
    static const int load_factor = 10;
    static const int expand_factor = 2;
    static const int starting_length = 2;

public:
    //for test only
    int totalAmount;
    int totalAmountDeleted;

     int totalAmount222;
    int  totalAmountDeleted222;
    HashTable()
    {
        employees = new MyList*[starting_length];
        itamar_check++;
        for (int i = 0; i < starting_length; i++)
        {
            employees[i] = new MyList();
            itamar_check++;
        }
        arraySize = starting_length;
        currentAmount = 0;

        // for test only
        totalAmount = 0;
        totalAmountDeleted = 0;
        totalAmount222 = 0;
        totalAmountDeleted222 = 0;

    }

     ~HashTable()
      {
          for (int i = 0; i < arraySize; i++)
          {
              if (employees[i] != NULL)
              {
                int x = employees[i]->DeleteAllList();
                  totalAmountDeleted += x;
                  totalAmountDeleted222 += x;
                  delete employees[i];
              }
              employees[i] = NULL;

          }
          delete[] employees;
      }

    int GetHashKey(int id) const
    {
        return id % arraySize;
    }

    void ExpandSize()
    {
        PrintHash();
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
        MyNode* ptrDoDelete;
        currentAmount = 0;
        int counter = 0;
        for (int i = 0; i < original_size ; i++)
        {
            if (temp[i]->GetFirstNode() != NULL) {
                ptr = temp[i]->GetFirstNode();
                while (ptr != NULL) {
                    ptrDoDelete = ptr;
                    Insert(ptr->GetValue());
                    counter++;
                    ptr = ptr->GetNext();
                    ptrDoDelete->SetValueToNull();
                }
            }
            temp[i]->DeleteAllList();
            delete(temp[i]);

        }
        delete[] temp;
        PrintHash();
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
        currentAmount = 0;
        MyNode* ptr;
        MyNode* ptrDoDelete;
        int counter = 0;
        for (int i = 0; i < original_size ; i++)
        {
            if (temp[i] != NULL) {
                if (temp[i]->GetFirstNode() != NULL)
                {
                    ptr = temp[i]->GetFirstNode();
                    while (ptr != NULL) {
                        ptrDoDelete = ptr;
                        Insert(ptr->GetValue());
                        counter++;
                        ptr = ptr->GetNext();
                        ptrDoDelete->SetValueToNull();
                    }
                }
            }
            temp[i]->DeleteAllList();
            delete(temp[i]);
        }
        delete[] temp;
    }

    bool Insert(Employee* employee)
    {
        int id = employee->GetEmployeeId();
            int key = GetHashKey(id);

        bool exist = employees[key]->IsExist(id);
        if (exist)
        {
            return false;
        }
        else
        {
            if (currentAmount >= load_factor * arraySize)
            {
                ExpandSize();
            }
            key = GetHashKey(id);
            employees[key]->InsertAtBeginning(employee);
            currentAmount++;
            return true;
        }

    }

    bool DeleteById(int id)
    {
        int key = GetHashKey(id);
        bool exist = employees[key]->IsExist(id);
        if (exist)
        {
            key = GetHashKey(id);
            employees[key]->DeleteFromList(id);
            currentAmount--;
            if (currentAmount <= arraySize * free_factor && arraySize >= starting_length)
            {
                ReduceSize();
            }
            return true;
        }
        return false;
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


    bool IsHashTableIsValid()
    {
            MyNode* ptr;
            for (int i = 0; i < arraySize; i++)
            {
                if (employees[i] != NULL)
                {
                    if (!employees[i]->ListIsValid())
                    {
                        return false;
                    }
                    if (employees[i] != NULL)
                    {
                      if (employees[i]->GetFirstNode() != NULL)
                      {
                           ptr = employees[i]->GetFirstNode();
                           while (ptr != NULL)
                           {
                              assert (ptr->GetValue()->GetEmployeeId() % arraySize == i);
                              ptr = ptr->GetNext();
                            }
                      }
                    }
                }
            }
            return true;
    }

    int GetArraySize()
    {
        return arraySize;
    }
};

#endif
