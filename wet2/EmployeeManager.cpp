#include "EmployeeManager.h"

Employee::Employee(int id, int grade, int salary, int companyId) : id(id), gradeValueInCompany(grade),
                                                                   gradeValueInAllEmployees(grade), salary(salary),
                                                                   companyId(companyId) {};

int Employee::GetEmployeeId() { return id; }

int Employee::GetGradeValueInCompany() { return gradeValueInCompany; }

int Employee::GetGradeValueInAllEmployees() { return gradeValueInAllEmployees; }

int Employee::GetSalary() { return salary; }

int Employee::GetCompanyId() { return companyId; }

void Employee::SetCompany(int newCompanyId) { companyId = newCompanyId; }

void Employee::IncreaseGrade(int BumpGrade,
                             bool isCompany) { if (isCompany) { gradeValueInCompany += BumpGrade; } else { gradeValueInAllEmployees += BumpGrade; }}

void Employee::IncreaseGradeInCompany(int BumpGrade) { gradeValueInCompany = gradeValueInCompany + BumpGrade; }

void Employee::IncreaseGradeInAllEmployees(int BumpGrade) {
    gradeValueInAllEmployees = gradeValueInAllEmployees + BumpGrade;
}

void Employee::IncreaseSalary(int SalaryIncrease) { salary = salary + SalaryIncrease; }

bool Employee::IsSalaryInRange(int minSalary, int maxSalary) { return (salary >= minSalary && salary <= maxSalary); }

bool Employee::IsSalaryBiggerThanZero() { return (salary > 0); }

int Employee::GetGrade(bool isCompany) {
    if (isCompany)
        return gradeValueInCompany;
    else
        return gradeValueInAllEmployees;
}


Company::Company(int id) : id(id), value(id), amountOfEmployees(0), amountOfNewEmployees(0),
                           totalGradesOfNewEmployees(0) {
    companyEmployees = new Map<Employee *, SalaryId>(true);
};

Company::~Company() {
    delete companyEmployees;
}

int Company::GetCompanyId() { return id; }

double Company::GetCompanyValue() { return value; }

int Company::GetCompanyAmountOfEmployees() { return amountOfEmployees; }

void Company::IncreaseValue(double add) { value += add; }

void Company::SetTotalValue(double newValue) { value = newValue; }

void Company::SetCompanyEmployees(Map<Employee *, SalaryId> *NewcompanyEmployees) {
    companyEmployees = NewcompanyEmployees;
};

void Company::IncreaseAmountOfEmployees(int addAmount) { amountOfEmployees += addAmount; }

Map<Employee *, SalaryId> *Company::GetCompanyEmployees() { return companyEmployees; }

int Company::GetAmountOfNewEmployees() { return amountOfNewEmployees; }

int Company::GetTotalGradeOfNewEmployees() { return totalGradesOfNewEmployees; }

void Company::IncreaseAmountOfNewEmployees(int amountToAdd) { amountOfNewEmployees += amountToAdd; }

void Company::IncreaseTotalGradesOfNewEmployees(int amountToAdd) { totalGradesOfNewEmployees += amountToAdd; }


