#ifndef DATA_STRUCTURES_234218_EmployeeManager
#define DATA_STRUCTURES_234218_EmployeeManager

class Company;

class Employee
{
private:
    int id;
    int grade;
    int salary;
    Company* company;

public:
    Employee(int id, int grade, int salary, Company* company);
    int GetEmployeeId();
    int GetGrade();
    int GetSalary();
    Company* GetCompany();

    int GetCompanyId();

    void IncreaseGrade(int BumpGrade);
    void IncreaseSalary(int SalaryIncrease);
    bool IsSalaryInRange(int minSalary, int maxSalary);
    bool IsSalaryBiggerThanZero();
};


class Company
{
private:
    Company* ownerCompany; // ownerCompany == Null if there is no owner company
    int id;
    int value;
    int amountOfEmployees;

public:
    Company(int id);
    int GetCompanyId();
    int GetCompanyValue();
    int GetCompanyAmountOfEmployees();
    void IncreaseAmountOfEmployees(int addAmount);
};


#endif //DATA_STRUCTURES_234218_EmployeeManager
