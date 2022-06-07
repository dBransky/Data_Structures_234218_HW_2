
#include "HighTech.h"


// in C need to check that k > 0...
HighTech::HighTech(int k) : amountOfNewEmployees(0), totalOfGradeOfNewEmployees(0),
                            amountOfEmployeesWithSalaryBiggerThenZero(0), companies(k), allEmployees(),
                            newEmployees() {}

HighTech::~HighTech() {
    companies.FreeAll();
    newEmployees.FreeAll();
}

void HighTech::AddEmployee(int EmployeeId, int CompanyId, int Grade) {
    if (EmployeeId <= 0 || CompanyId <= 0 || CompanyId > companies.GetK() || Grade < 0) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) != NULL) {
        assert(allEmployees.check_is_valid());
        throw Failure();
    }
    int correctCompanyId = companies.Find(CompanyId); // O(log* k)
    newEmployees.Insert(new Employee(EmployeeId, Grade, 0, correctCompanyId));
    Company *company = companies.GetCorrectCompanyPosByConst(correctCompanyId);
    company->IncreaseAmountOfNewEmployees(1);
    company->IncreaseTotalGradesOfNewEmployees(Grade);
    amountOfNewEmployees++;
    totalOfGradeOfNewEmployees += Grade;
    assert(allEmployees.check_is_valid());
}

void HighTech::RemoveEmployee(int EmployeeId) {
    if (EmployeeId <= 0) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    Employee *employee = newEmployees.FindById(EmployeeId);
    if (employee == NULL) {
        assert(allEmployees.check_is_valid());
        throw Failure();
    }
    if (employee->IsSalaryBiggerThanZero()) {
        allEmployees.remove(SalaryId(employee->GetSalary(), EmployeeId));//log n
        int correctCompany = companies.Find(employee->GetCompanyId());
        Company *company = companies.GetCorrectCompanyPosByConst(correctCompany);
        company->IncreaseAmountOfEmployees(-1);
        companies.GetCorrectCompanyPosByConst(employee->GetCompanyId())->GetCompanyEmployees().remove(SalaryId(employee->GetSalary(), EmployeeId));
        amountOfEmployeesWithSalaryBiggerThenZero--;
    } else {
        Company *company = companies.GetCorrectCompanyPosByConst(employee->GetCompanyId());
        company->IncreaseAmountOfNewEmployees(-1);
        company->IncreaseTotalGradesOfNewEmployees(employee->GetGrade() * (-1));
        amountOfNewEmployees--;
        totalOfGradeOfNewEmployees -= employee->GetGrade();
    }
    newEmployees.DeleteById(EmployeeId); // this function also free the employee.
    assert(allEmployees.check_is_valid());
}

void HighTech::AcquireCompany(int AcquireId, int TargetId, double Factor) {
    if (AcquireId <= 0 || AcquireId > companies.GetK() || TargetId <= 0 || TargetId > companies.GetK()) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    if (companies.Find(AcquireId) == companies.Find(TargetId) || Factor <= 0.0) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    Company *AcquireCompany = companies.GetCorrectCompanyPosByConst(AcquireId);
    Company *TargetCompany = companies.GetCorrectCompanyPosByConst(TargetId);
    int amountOfEmployees = TargetCompany->GetCompanyAmountOfEmployees();
    int amountOfNewEmployees = TargetCompany->GetAmountOfNewEmployees();
    int totalGrades = TargetCompany->GetTotalGradeOfNewEmployees();
    AcquireCompany->GetCompanyEmployees().merge(TargetCompany->GetCompanyEmployees());
    AcquireCompany->IncreaseAmountOfEmployees(amountOfEmployees);
    AcquireCompany->IncreaseAmountOfNewEmployees(amountOfNewEmployees);
    AcquireCompany->IncreaseTotalGradesOfNewEmployees(totalGrades);
    Pair<Employee *, SalaryId> *pair_list = AcquireCompany->GetCompanyEmployees().GetFirstNum(AcquireCompany->GetCompanyAmountOfEmployees());
    for (int i = 0; i < AcquireCompany->GetCompanyAmountOfEmployees(); i++)
    {
        pair_list[i].element->SetCompany(AcquireId);
        pair_list[i].element = NULL;
    }
    companies.Union(companies.Find(AcquireId), companies.Find(TargetId), Factor);
    assert(allEmployees.check_is_valid());
}

void HighTech::EmployeeSalaryIncrease(int EmployeeId, int SalaryIncrease) {
    if (EmployeeId <= 0 || SalaryIncrease <= 0) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) == NULL) {
        assert(allEmployees.check_is_valid());
        throw Failure();
    }
    Company* company = companies.GetCorrectCompanyPosByConst(newEmployees.FindById(EmployeeId)->GetCompanyId());
    Employee *employee = newEmployees.FindById(EmployeeId);
    if (employee->GetSalary() != 0) {
        allEmployees.remove(SalaryId(employee->GetSalary(), EmployeeId));
        company->GetCompanyEmployees().remove(SalaryId(employee->GetSalary(), EmployeeId));
    } else {
        amountOfEmployeesWithSalaryBiggerThenZero++;
        company->IncreaseAmountOfEmployees(1);
        company->IncreaseTotalGradesOfNewEmployees(-1);
        company->IncreaseTotalGradesOfNewEmployees(-1 * employee->GetGrade());
        amountOfNewEmployees--;
        totalOfGradeOfNewEmployees -= employee->GetSalary();
    }
    newEmployees.FindById(EmployeeId)->IncreaseSalary(SalaryIncrease);
    allEmployees.insert(SalaryId(employee->GetSalary(), EmployeeId), employee);
    company->GetCompanyEmployees().insert(SalaryId(employee->GetSalary(), EmployeeId),employee);
}

void HighTech::PromoteEmployee(int EmployeeId, int BumpGrade) {
    if (EmployeeId <= 0) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) == NULL) {
        assert(allEmployees.check_is_valid());
        throw Failure();
    }
    assert(allEmployees.check_is_valid());
    if (BumpGrade > 0) {
        Employee* employee = newEmployees.FindById(EmployeeId);
        assert(allEmployees.check_is_valid());
        if (newEmployees.FindById(EmployeeId)->GetSalary() == 0)
        {
            companies.GetCorrectCompanyPosByConst(newEmployees.FindById(EmployeeId)->GetCompanyId())->IncreaseTotalGradesOfNewEmployees(1);
            totalOfGradeOfNewEmployees++;
        }
        else
        {
            assert(allEmployees.check_is_valid());
            allEmployees.remove(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId));
            assert(allEmployees.check_is_valid());
            companies.GetCorrectCompanyPosByConst(newEmployees.FindById(EmployeeId)->GetCompanyId())->GetCompanyEmployees().remove(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId));
            newEmployees.FindById(EmployeeId)->IncreaseGrade(1);
            allEmployees.insert(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId),employee);
            companies.GetCorrectCompanyPosByConst(newEmployees.FindById(EmployeeId)->GetCompanyId())->GetCompanyEmployees().insert(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId),employee);
        }
    }
    assert(allEmployees.check_is_valid());
}

void HighTech::SumOfBumpGradeBetweenTopWorkersByGroup(int CompanyId, int m, int *sumBumpGrade) {
    if (sumBumpGrade == NULL || m <= 0 || CompanyId < 0 || CompanyId > companies.GetK()) {
        throw InvalidInput();
    }
    int totalSum = 0;
    if (CompanyId > 0) {
        if (companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyAmountOfEmployees() < m) {
            assert(allEmployees.check_is_valid());
            throw Failure();
        } else {
            totalSum = companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees().SumGrades(m);
        }
    } else {
        if (amountOfEmployeesWithSalaryBiggerThenZero < m) {
            assert(allEmployees.check_is_valid());
            throw Failure();
        } else {
            totalSum = allEmployees.SumGrades(m);
        }
    }
    *sumBumpGrade = totalSum;
    std::cout << "SumOfBumpGradeBetweenTopWorkersByGroup: " << ((int) *sumBumpGrade) << std::endl;
    assert(allEmployees.check_is_valid());
}

void HighTech::AverageBumpGradeBetweenSalaryByGroup(int CompanyId, int lowerSalary, int higherSalary,
                                                    double *averageBumpGrade) {
    if (averageBumpGrade == NULL || higherSalary < 0 || lowerSalary < 0 || higherSalary < lowerSalary ||
        CompanyId > companies.GetK() || CompanyId < 0) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    double totalSum = 0.0;
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
        totalAmount += companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees().AmountMinMax(
                SalaryId(higherSalary, INT32_MAX), SalaryId(lowerSalary, 0));
        totalSum += companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees().SumMinMax(SalaryId(higherSalary, INT32_MAX),
                                                                                     SalaryId(lowerSalary, 0));
        if (totalAmount == 0) {
            assert(allEmployees.check_is_valid());
            throw Failure();
        }
    } else {
        totalAmount += allEmployees.AmountMinMax(SalaryId(higherSalary, INT32_MAX), SalaryId(lowerSalary, 0));
        totalSum += allEmployees.SumMinMax(SalaryId(higherSalary, INT32_MAX), SalaryId(lowerSalary, 0));
        if (totalAmount == 0) {
            assert(allEmployees.check_is_valid());
            throw Failure();
        }
    }
    *averageBumpGrade = totalSum / totalAmount;
    std::cout << "AverageBumpGradeBetweenSalaryByGroup: " << ((double) *averageBumpGrade + 0.0) << std::endl;
    assert(allEmployees.check_is_valid());
}

void HighTech::CompanyValue(int CompanyId, double *standing) {
    if (standing == NULL || CompanyId > companies.GetK() || CompanyId <= 0) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    *standing = companies.GetCompanyValue(CompanyId); // O(log* k)
    std::cout << "CompanyValue: " << *standing << std::endl;
    assert(allEmployees.check_is_valid());
}


//Extra

void HighTech::BumpGradeToEmployees(int lowerSalary, int higherSalary, int BumpGrade) {

}



