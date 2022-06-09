#ifndef MY_UNION_FIND
#define MY_UNION_FIND

#include <iostream>
#include "EmployeeManager.h"

class UnionFind
{
private:
    int ItamarGlobal;
    int K;
    int* size;
    int* parents;
    double* salaryIncrease;
    Company** elements;
    Company** elementsPos;

public:
    UnionFind(int k);
    int Find(int CompanyId);
    Company* GetCompany(int CompanyId);
    Company* GetCompanyById(int companyId);
    double GetCompanyValue(int CompanyId);
    Company* GetCorrectCompanyPosByConst(int CompanyId);
    void Itamar(int companyId, double value);
    void Union(int acquire, int target, double Factor);
    void FreeAll();
    int GetK();
    void PrintStatus();
};


#endif