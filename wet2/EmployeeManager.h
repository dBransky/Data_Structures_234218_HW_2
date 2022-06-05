#ifndef DATA_STRUCTURES_234218_EmployeeManager
#define DATA_STRUCTURES_234218_EmployeeManager

class Company;
class ReverseTree;

class Employee
{
private:
    int id;
    int grade;
    int salary;
    int companyId;

public:
    Employee(int id, int grade, int salary, int companyId);
    int GetEmployeeId();
    int GetGrade();
    int GetSalary();
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
    double value;
    int amountOfEmployees;

public:
    Company(int id);
    int GetCompanyId();
    double GetCompanyValue();
    int GetCompanyAmountOfEmployees();
    void IncreaseValue(double add);
    void SetTotalValue(double newValue);
    void IncreaseAmountOfEmployees(int addAmount);
};


#endif //DATA_STRUCTURES_234218_EmployeeManager
