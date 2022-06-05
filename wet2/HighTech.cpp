
#include "HighTech.h"

class Exceptions : public std::exception {};

class Failure : public Exceptions {};

class InvalidInput : public Exceptions {};


HighTech::HighTech(int k)
{
    if (k > 0) {
        companies = new UnionFind(k);
        allEmployees = new RankTree();
        newEmployees = new HashTable();
    }
}

HighTech::~HighTech()
{
    /*
    companies.DeleteAll();
    allEmployees.DeleteAll();
    newEmployees.DeleteAll();
    */
}

void HighTech::addEmployee(int EmployeeId, int CompanyId, int Grade)
{
    if (EmployeeId <= 0 || CompanyId <= 0 || CompanyId > companies->GetK() || Grade < 0)
    {
        throw InvalidInput();
    }
    if (newEmployees->FindById(EmployeeId) != NULL)
    {
        throw Failure();
    }
    int correctCompanyId = companies->Find(CompanyId); // O(log* k)
    newEmployees->Insert(new Employee(EmployeeId, Grade, 0, correctCompanyId));
}

void HighTech::removeEmployee(int EmployeeId)
{

}

void HighTech::acquireCompany(int AcquireId, int TargetId, double Factor)
{
    if (AcquireId <= 0 || AcquireId > companies->GetK() || TargetId <= 0 || TargetId > companies->GetK())
    {
        throw InvalidInput();
    }
    if (companies->Find(AcquireId) == companies->Find(TargetId) || Factor <= 0.0)
    {
        throw InvalidInput();
    }
    companies->Union(AcquireId, TargetId, Factor);
    // Now Merge With Rank Tree
}

void HighTech::employeeSalaryIncrease(int EmployeeId, int SalaryIncrease)
{
    if (EmployeeId <= 0 || SalaryIncrease <= 0)
    {
        throw InvalidInput();
    }
    if (newEmployees->FindById(EmployeeId) == NULL)
    {
        throw Failure();
    }
    int companyId = newEmployees->FindById(EmployeeId)->GetCompanyId();
    // remove from company rank tree
    // remove from all employees rank tree
    newEmployees->FindById(EmployeeId)->IncreaseSalary(SalaryIncrease);
    // add to company rank tree
    // add to all employees rank tree
}

void HighTech::promoteEmployee(int EmployeeId, int BumpGrade)
{
    if (EmployeeId <= 0)
    {
        throw InvalidInput();
    }
    if (newEmployees->FindById(EmployeeId) == NULL)
    {
        throw Failure();
    }
    if (BumpGrade > 0)
    {
        newEmployees->FindById(EmployeeId)->IncreaseGrade(1);
    }
    else
    {
        // nothing to do...
    }
}


void HighTech::sumOfBumpGradeBetweenTopWorkersByGroup(int CompanyId, int m, int *sumBumpGrade)
{

}

void HighTech::averageBumpGradeBetweenSalaryByGroup(int CompanyId, int lowerSalary, int higherSalary, double *averageBumpGrade)
{

}

void HighTech::companyValue(int CompanyId, double *standing)
{
    if (standing == NULL || CompanyId > companies->GetK() || CompanyId <= 0)
    {
        throw InvalidInput();
    }
    *standing = companies->GetCompany(CompanyId)->GetCompanyValue();
}


//Extra

void HighTech::bumpGradeToEmployees(int lowerSalary, int higherSalary, int BumpGrade)
{

}



