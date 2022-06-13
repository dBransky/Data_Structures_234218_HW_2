#ifndef DATA_STRUCTURES_234218_EmployeeManager
#define DATA_STRUCTURES_234218_EmployeeManager

#include "MyMap.h"

class SalaryId {
    int id;

    friend bool operator>(SalaryId id1, SalaryId id2) {
        return ((id1.salary == id2.salary && id1.id > id2.id) || id1.salary > id2.salary);
    }

    friend bool operator<(SalaryId id1, SalaryId id2) {
        return !(id1 > id2) && !(id1 == id2);
    }

    friend bool operator==(SalaryId id1, SalaryId id2) {
        return (id1.salary == id2.salary) && (id1.id == id2.id);
    }

    friend bool operator>=(SalaryId id1, SalaryId id2) {
        return ((id1.salary == id2.salary && id1.id >= id2.id) || (id1.salary > id2.salary));
    }

    friend bool operator<=(SalaryId id1, SalaryId id2) {
        return id2 >= id1;
    }

public:
    double salary;

    SalaryId() = default;

    SalaryId(double salary, int id) : salary(salary), id(id) {}
};

class Employee {
private:
    int id;
    int gradeValueInCompany;
    int gradeValueInAllEmployees;
    int salary;
    int companyId;

public:
    Employee(int id, int grade, int salary, int companyId);

    int GetEmployeeId();

    int GetGradeValueInCompany();

    int GetGradeValueInAllEmployees();

    int GetSalary();

    int GetCompanyId();

    void IncreaseGrade(int BumpGrade, bool isCompany);

    int GetGrade(bool isCompany);

    void SetCompany(int newCompanyId);

    void IncreaseGradeInCompany(int BumpGrade);

    void IncreaseGradeInAllEmployees(int BumpGrade);

    void IncreaseSalary(int SalaryIncrease);

    bool IsSalaryInRange(int minSalary, int maxSalary);

    bool IsSalaryBiggerThanZero();
};


class Company {
private:
    int id;
    double value;
    int amountOfEmployees;
    int amountOfNewEmployees;
    int totalGradesOfNewEmployees;
    Map<Employee *, SalaryId> *companyEmployees;

public:
    Company(int id);

    ~Company();

    int GetCompanyId();

    double GetCompanyValue();

    int GetCompanyAmountOfEmployees();

    void IncreaseValue(double add);

    void SetTotalValue(double newValue);

    void IncreaseAmountOfEmployees(int addAmount);

    void SetCompanyEmployeesToNull();

    void SetCompanyEmployees(Map<Employee *, SalaryId> *NewcompanyEmployees);

    Map<Employee *, SalaryId> *GetCompanyEmployees();

    int GetAmountOfNewEmployees();

    int GetTotalGradeOfNewEmployees();

    void IncreaseAmountOfNewEmployees(int amountToAdd);

    void IncreaseTotalGradesOfNewEmployees(int amountToAdd);

};


#endif //DATA_STRUCTURES_234218_EmployeeManager
