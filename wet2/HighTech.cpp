#include "HighTech.h"

HighTech::HighTech(int k) : amountOfNewEmployees(0), totalOfGradeOfNewEmployees(0),
                            amountOfEmployeesWithSalaryBiggerThenZero(0), companies(k), allEmployees(), newEmployees() {
}

HighTech::~HighTech()
{

}

void HighTech::AddEmployee(int EmployeeId, int CompanyId, int Grade) {
    if (EmployeeId <= 0 || CompanyId <= 0 || CompanyId > companies.GetK() || Grade < 0) {
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) != NULL) {
        throw Failure();
    }
    int correctCompanyId = companies.Find(CompanyId); // O(log* k)
    Employee* employee = new Employee(EmployeeId, Grade, 0, correctCompanyId);
    newEmployees.Insert(employee);
    Company *company = companies.GetCorrectCompanyPosByConst(correctCompanyId);
    company->IncreaseAmountOfNewEmployees(1);
    company->IncreaseTotalGradesOfNewEmployees(Grade);
    amountOfNewEmployees++;
    totalOfGradeOfNewEmployees += Grade;
}

void HighTech::RemoveEmployee(int EmployeeId) {
    if (EmployeeId <= 0) {
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) == NULL) {
        throw Failure();
    }
    Employee *employee = newEmployees.FindById(EmployeeId);
    employee->SetCompany(companies.GetCorrectCompanyPosByConst(employee->GetCompanyId())->GetCompanyId());
    if (employee->IsSalaryBiggerThanZero()) {
        allEmployees.remove(SalaryId(employee->GetSalary(), EmployeeId));//log n
        int correctCompany = companies.Find(employee->GetCompanyId());
        Company *company = companies.GetCorrectCompanyPosByConst(employee->GetCompanyId());
        company->IncreaseAmountOfEmployees(-1);
        companies.GetCorrectCompanyPosByConst(employee->GetCompanyId())->GetCompanyEmployees()->remove(SalaryId(employee->GetSalary(), EmployeeId));
        amountOfEmployeesWithSalaryBiggerThenZero--;
    } else {
        Company *company = companies.GetCorrectCompanyPosByConst(employee->GetCompanyId());
        company->IncreaseAmountOfNewEmployees(-1);
        company->IncreaseTotalGradesOfNewEmployees(employee->GetGrade() * (-1));
        amountOfNewEmployees--;
        totalOfGradeOfNewEmployees -= employee->GetGrade();
    }
    newEmployees.DeleteById(EmployeeId); // this function also free the employee.
}

void HighTech::AcquireCompany(int AcquireId, int TargetId, double Factor) {
    if (AcquireId <= 0 || AcquireId > companies.GetK() || TargetId <= 0 || TargetId > companies.GetK()) {
        throw InvalidInput();
    }
    if (companies.Find(AcquireId) == companies.Find(TargetId) || Factor <= 0.0) {
        throw InvalidInput();
    }
    Company *AcquireCompany = companies.GetCorrectCompanyPosByConst(AcquireId);
    Company *TargetCompany = companies.GetCorrectCompanyPosByConst(TargetId);
    int amountOfEmployees = TargetCompany->GetCompanyAmountOfEmployees();
    int amountOfNewEmployees = TargetCompany->GetAmountOfNewEmployees();
    int totalGrades = TargetCompany->GetTotalGradeOfNewEmployees();
    AcquireCompany->GetCompanyEmployees()->merge(*TargetCompany->GetCompanyEmployees());
    AcquireCompany->IncreaseAmountOfEmployees(amountOfEmployees);
    TargetCompany->IncreaseAmountOfEmployees(-amountOfEmployees);
    AcquireCompany->IncreaseAmountOfNewEmployees(amountOfNewEmployees);
    AcquireCompany->IncreaseTotalGradesOfNewEmployees(totalGrades);
    Pair<Employee *, SalaryId> *pair_list = AcquireCompany->GetCompanyEmployees()->GetFirstNum(AcquireCompany->GetCompanyAmountOfEmployees());
    int totalAmount = AcquireCompany->GetCompanyAmountOfEmployees();
    for (int i = 0; i < totalAmount; i++)
    {
        pair_list[i].element->SetCompany(AcquireCompany->GetCompanyId());
        pair_list[i].element = NULL;
    }
    delete[] (pair_list);
    companies.Union(companies.Find(AcquireCompany->GetCompanyId()), companies.Find(TargetCompany->GetCompanyId()), Factor);
}

void HighTech::EmployeeSalaryIncrease(int EmployeeId, int SalaryIncrease) {
    if (EmployeeId <= 0 || SalaryIncrease <= 0) {
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) == NULL) {
        throw Failure();
    }
    Employee *employee = newEmployees.FindById(EmployeeId);
    employee->SetCompany(companies.GetCorrectCompanyPosByConst(employee->GetCompanyId())->GetCompanyId());
    Company* company = companies.GetCorrectCompanyPosByConst(employee->GetCompanyId());
    if (employee->GetSalary() != 0) {
        allEmployees.remove(SalaryId(employee->GetSalary(), EmployeeId));
        company->GetCompanyEmployees()->remove(SalaryId(employee->GetSalary(), EmployeeId));
    } else {
        amountOfEmployeesWithSalaryBiggerThenZero++;
        company->IncreaseAmountOfEmployees(1);
        company->IncreaseAmountOfNewEmployees(-1);
        company->IncreaseTotalGradesOfNewEmployees(-1 * employee->GetGrade());
        amountOfNewEmployees--;
        totalOfGradeOfNewEmployees -= employee->GetGrade();
    }
    employee->IncreaseSalary(SalaryIncrease);
    allEmployees.insert(SalaryId(employee->GetSalary(), EmployeeId), employee);
    company->GetCompanyEmployees()->insert(SalaryId(employee->GetSalary() , EmployeeId),employee);
}

void HighTech::PromoteEmployee(int EmployeeId, int BumpGrade) {
    if (EmployeeId <= 0) {
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) == NULL) {
        throw Failure();
    }
    if (BumpGrade > 0) {
        Employee *employee = newEmployees.FindById(EmployeeId);
        employee->SetCompany(companies.GetCorrectCompanyPosByConst(employee->GetCompanyId())->GetCompanyId());
        if (newEmployees.FindById(EmployeeId)->GetSalary() == 0)
        {
            newEmployees.FindById(EmployeeId)->IncreaseGrade(BumpGrade);
            companies.GetCorrectCompanyPosByConst(newEmployees.FindById(EmployeeId)->GetCompanyId())->IncreaseTotalGradesOfNewEmployees(BumpGrade);
            totalOfGradeOfNewEmployees += BumpGrade;
        }
        else
        {
            allEmployees.remove(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId));
            companies.GetCorrectCompanyPosByConst(newEmployees.FindById(EmployeeId)->GetCompanyId())->GetCompanyEmployees()->remove(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId));
            newEmployees.FindById(EmployeeId)->IncreaseGrade(BumpGrade);
            allEmployees.insert(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId),employee);
            companies.GetCorrectCompanyPosByConst(newEmployees.FindById(EmployeeId)->GetCompanyId())->GetCompanyEmployees()->insert(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId),employee);
        }
    }
}

void HighTech::SumOfBumpGradeBetweenTopWorkersByGroup(int CompanyId, int m) {
    if (m <= 0 || CompanyId < 0 || CompanyId > companies.GetK()) {
        throw InvalidInput();
    }
    long int totalSum;
    if (CompanyId > 0) {
        if (companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyAmountOfEmployees() < m) {
            throw Failure();
        } else {
            totalSum = companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees()->SumGrades(m);
        }
    } else {
        if (amountOfEmployeesWithSalaryBiggerThenZero < m) {
            throw Failure();
        } else {
            totalSum = allEmployees.SumGrades(m);
        }
    }
    std::cout << "SumOfBumpGradeBetweenTopWorkersByGroup: " << ((int) totalSum) << std::endl;
}

void HighTech::AverageBumpGradeBetweenSalaryByGroup(int CompanyId, int lowerSalary, int higherSalary)
{
    if (higherSalary < 0 || lowerSalary < 0 || higherSalary < lowerSalary ||
        CompanyId > companies.GetK() || CompanyId < 0) {
        throw InvalidInput();
    }
    if (CompanyId != 0)
    {
        CompanyId = companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyId();
    }
    long double totalSum = 0.0;
    double totalAmount = 0.0;
    if (lowerSalary == 0) {
        if (CompanyId == 0) {
            totalSum += totalOfGradeOfNewEmployees;
            totalAmount += amountOfNewEmployees;
        } else {
            totalSum += companies.GetCorrectCompanyPosByConst(CompanyId)->GetTotalGradeOfNewEmployees();
            totalAmount += companies.GetCorrectCompanyPosByConst(CompanyId)->GetAmountOfNewEmployees();
        }
    }
    if (CompanyId > 0) {
        totalAmount += companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees()->AmountMinMax(
                SalaryId(higherSalary, INT32_MAX), SalaryId(lowerSalary, 0));
        totalSum += companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees()->SumMinMax(SalaryId(higherSalary, INT32_MAX),
                                                                                     SalaryId(lowerSalary, 0));
        if (totalAmount == 0) {
            throw Failure();
        }
    } else {
        totalAmount += allEmployees.AmountMinMax(SalaryId(higherSalary, INT32_MAX), SalaryId(lowerSalary, 0));
        totalSum += allEmployees.SumMinMax(SalaryId(higherSalary, INT32_MAX), SalaryId(lowerSalary, 0));
        if (totalAmount == 0) {
            throw Failure();
        }
    }
    long double averageBumpGrade = totalSum / totalAmount;
    std::cout << "AverageBumpGradeBetweenSalaryByGroup: " << averageBumpGrade << std::endl;
}

void HighTech::CompanyValue(int CompanyId) {
    if (CompanyId > companies.GetK() || CompanyId <= 0)
    {
        throw InvalidInput();
    }
    long double standing = companies.GetCompanyValue(CompanyId); // O(log* k)
    std::cout << "CompanyValue: " << standing << std::endl;
}



//Extra

void HighTech::BumpGradeToEmployees(int lowerSalary, int higherSalary, int BumpGrade) {

}



