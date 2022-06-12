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
    double* salaryIncrease;
    Company** elements;

public:
    void MyAssert();
    UnionFind(int k);
    ~UnionFind();
    int Find(int CompanyId);
    double GetCompanyValue(int CompanyId);
    Company* GetCorrectCompanyPosByConst(int CompanyId);
    void Union(int acquire, int target, double Factor);
    int GetK();

    // Delete In And
    void Itamar(int companyId, double value);
    void PrintStatus();
};

#endif