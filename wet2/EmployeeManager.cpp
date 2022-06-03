#include "EmployeeManager.h"


Employee::Employee(int id, int grade, int salary, Company* company) : id(id), grade(grade), salary(salary), company(company) {};
int Employee::GetEmployeeId() { return id; }
int Employee::GetGrade() { return grade; }
int Employee::GetSalary() { return salary; }
Company* Employee::GetCompany() { return company; }

int Employee::GetCompanyId() { return company->GetCompanyId(); }

void Employee::IncreaseGrade(int BumpGrade) { grade = grade + BumpGrade; }
void Employee::IncreaseSalary(int SalaryIncrease) { salary = salary + SalaryIncrease; }
bool Employee::IsSalaryInRange(int minSalary, int maxSalary) { return (salary >= minSalary && salary <= maxSalary); }
bool Employee::IsSalaryBiggerThanZero() { return (salary > 0); }



Company::Company(int id) : id(id), value(id), amountOfEmployees(0) {};
int Company::GetCompanyId() { return id; }
int Company::GetCompanyValue() { return value; }
int Company::GetCompanyAmountOfEmployees() { return amountOfEmployees; }
void Company::IncreaseAmountOfEmployees(int addAmount) { amountOfEmployees += addAmount; }