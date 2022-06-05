#ifndef MY_UNION_FIND
#define MY_UNION_FIND

#include <iostream>
#include "EmployeeManager.h"

class UnionFind
{
private:
    int K;
    int* size;
    int* parents;
    Company** elements;

public:
    UnionFind(int k);
    int Find(int CompanyId);
    Company* GetCompany(int CompanyId);
    void Union(int acquire, int target, double Factor);
    int GetK();
    void Itamar(int companyId, int value);
    void PrintStatus();
};


#endif