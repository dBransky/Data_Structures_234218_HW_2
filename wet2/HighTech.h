

#ifndef UNTITLED61_HIGHTECH_H
#define UNTITLED61_HIGHTECH_H

#include "MyHashTable.h"
#include "MyUnionFind.h"
#include "RankTree.h"


class HighTech
{
private:
    UnionFind* companies;
    RankTree* allEmployees;
    HashTable* newEmployees;


public:
    HighTech(int k);
    ~HighTech();
    void addEmployee(int EmployeeId, int CompanyId, int Grade);
    void removeEmployee(int EmployeeId);
    void acquireCompany(int AcquireId, int TargetId, double Factor);
    void employeeSalaryIncrease(int EmployeeId, int SalaryIncrease);
    void promoteEmployee(int EmployeeId, int BumpGrade);
    void sumOfBumpGradeBetweenTopWorkersByGroup(int CompanyId, int m, int* sumBumpGrade);
    void averageBumpGradeBetweenSalaryByGroup(int CompanyId, int lowerSalary, int higherSalary, double* averageBumpGrade);
    void companyValue(int CompanyId, double* standing);

    //Extra
    void bumpGradeToEmployees(int lowerSalary, int higherSalary, int BumpGrade);





};




#endif //UNTITLED61_HIGHTECH_H
