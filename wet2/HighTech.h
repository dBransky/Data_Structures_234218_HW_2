#ifndef UNTITLED61_HIGHTECH_H
#define UNTITLED61_HIGHTECH_H

#include "EmployeeManager.h"
#include "MyHashTable.h"
#include "MyUnionFind.h"
#include "MyMap.h"

class Exceptions : public std::exception {};

class Failure : public Exceptions {};

class InvalidInput : public Exceptions {};


class HighTech
{
private:
    int amountOfNewEmployees;
    double totalOfGradeOfNewEmployees;
    int amountOfEmployeesWithSalaryBiggerThenZero;
    int bonus_new_employees;
    UnionFind companies;
    Map<Employee*, SalaryId> allEmployees;
    HashTable newEmployees;

public:
    HighTech(int k);
    ~HighTech();
    void AddEmployee(int EmployeeId, int CompanyId, int Grade);
    void RemoveEmployee(int EmployeeId);
    void AcquireCompany(int AcquireId, int TargetId, double Factor);
    void EmployeeSalaryIncrease(int EmployeeId, int SalaryIncrease);
    void PromoteEmployee(int EmployeeId, int BumpGrade);
    void SumOfBumpGradeBetweenTopWorkersByGroup(int CompanyId, int m);
    void AverageBumpGradeBetweenSalaryByGroup(int CompanyId, int lowerSalary, int higherSalary);
    void CompanyValue(int CompanyId);

    //Extra
    void BumpGradeToEmployees(int lowerSalary, int higherSalary, int BumpGrade);





};




#endif //UNTITLED61_HIGHTECH_H
