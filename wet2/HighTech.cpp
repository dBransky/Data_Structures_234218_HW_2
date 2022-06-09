
#include "HighTech.h"

void HighTech::WTF() {
    if (companies.GetCorrectCompanyPosByConst(18)->GetCompanyEmployees() == NULL) {
        int x = 5;
    }
    for (int i = 0; i < 20; i++) {
        if (companies.GetCorrectCompanyPosByConst(i + 1)->GetCompanyEmployees() != NULL) {
            if (!companies.GetCorrectCompanyPosByConst(i + 1)->GetCompanyEmployees()->check_is_valid2(
                    companies.GetCorrectCompanyPosByConst(i + 1)->GetCompanyId()))
                int x = 6;
            if (companies.GetCorrectCompanyPosByConst(i + 1)->GetCompanyEmployees()->amount !=
                companies.GetCorrectCompanyPosByConst(i + 1)->GetCompanyAmountOfEmployees()) {
                int x = 7;
            }
        }
    }


}

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
    Employee *employee = new Employee(EmployeeId, Grade, 0, correctCompanyId);
    assert(employee != NULL);
    newEmployees.Insert(employee);
    Company *company = companies.GetCorrectCompanyPosByConst(correctCompanyId);
    company->IncreaseAmountOfNewEmployees(1);
    company->IncreaseTotalGradesOfNewEmployees(Grade);
    amountOfNewEmployees++;
    totalOfGradeOfNewEmployees += Grade;
    assert(allEmployees.check_is_valid());
    assert(company->GetCompanyEmployees()->check_is_valid());
    WTF();


}

void HighTech::RemoveEmployee(int EmployeeId) {
    if (EmployeeId <= 0) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    Employee *employee = newEmployees.FindById(EmployeeId);
    employee->SetCompany(companies.GetCorrectCompanyPosByConst(employee->GetCompanyId())->GetCompanyId());
    if (employee == NULL) {
        assert(allEmployees.check_is_valid());
        throw Failure();
    }
    if (employee->IsSalaryBiggerThanZero()) {
        allEmployees.remove(SalaryId(employee->GetSalary(), EmployeeId));//log n
        int correctCompany = companies.Find(employee->GetCompanyId());
        Company *company = companies.GetCorrectCompanyPosByConst(employee->GetCompanyId());
        company->IncreaseAmountOfEmployees(-1);
        companies.GetCorrectCompanyPosByConst(employee->GetCompanyId())->GetCompanyEmployees()->remove(
                SalaryId(employee->GetSalary(), EmployeeId));
        amountOfEmployeesWithSalaryBiggerThenZero--;
        assert(company->GetCompanyEmployees()->check_is_valid());

    } else {
        Company *company = companies.GetCorrectCompanyPosByConst(employee->GetCompanyId());
        company->IncreaseAmountOfNewEmployees(-1);
        company->IncreaseTotalGradesOfNewEmployees(employee->GetGrade() * (-1));
        amountOfNewEmployees--;
        totalOfGradeOfNewEmployees -= employee->GetGrade();
        assert(company->GetCompanyEmployees()->check_is_valid());


    }
    newEmployees.DeleteById(EmployeeId); // this function also free the employee.
    assert(allEmployees.check_is_valid());
    WTF();


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
    if (AcquireId == 2 && TargetId == 11) {
        int y = 1;
    }
    Company *AcquireCompany = companies.GetCorrectCompanyPosByConst(AcquireId);
    Company *TargetCompany = companies.GetCorrectCompanyPosByConst(TargetId);
    int amountOfEmployees = TargetCompany->GetCompanyAmountOfEmployees();
    int amountOfNewEmployees = TargetCompany->GetAmountOfNewEmployees();
    int totalGrades = TargetCompany->GetTotalGradeOfNewEmployees();
    if (AcquireCompany->GetCompanyEmployees() == NULL && TargetCompany->GetCompanyEmployees() != NULL) {
        AcquireCompany->SetCompanyEmployees(new Map<Employee *, SalaryId>());
    }
    if (TargetCompany->GetCompanyEmployees() != NULL) {
        AcquireCompany->GetCompanyEmployees()->merge(*TargetCompany->GetCompanyEmployees());
    }
    AcquireCompany->IncreaseAmountOfEmployees(amountOfEmployees);
    TargetCompany->IncreaseAmountOfEmployees(-amountOfEmployees);
    AcquireCompany->IncreaseAmountOfNewEmployees(amountOfNewEmployees);
    AcquireCompany->IncreaseTotalGradesOfNewEmployees(totalGrades);
    Pair<Employee *, SalaryId> *pair_list = AcquireCompany->GetCompanyEmployees()->GetFirstNum(
            AcquireCompany->GetCompanyAmountOfEmployees());
    int x = AcquireCompany->GetCompanyAmountOfEmployees();
    for (int i = 0; i < x; i++) {
        pair_list[i].element->SetCompany(AcquireCompany->GetCompanyId());
        pair_list[i].element = NULL;
    }

    delete[] (pair_list);
    companies.Union(companies.Find(AcquireCompany->GetCompanyId()), companies.Find(TargetCompany->GetCompanyId()),
                    Factor);
    TargetCompany->SetCompanyEmployeesToNull();
    assert(allEmployees.check_is_valid());
    assert(AcquireCompany->GetCompanyEmployees()->check_is_valid());
    WTF();

}

void HighTech::EmployeeSalaryIncrease(int EmployeeId, int SalaryIncrease) {
    WTF();
    if (EmployeeId == 20 && SalaryIncrease == 1) {
        int x = 5;
    }
    if (EmployeeId <= 0 || SalaryIncrease <= 0) {
        // assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) == NULL) {
        // assert(allEmployees.check_is_valid());
        throw Failure();
    }
    Employee *employee = newEmployees.FindById(EmployeeId);
    employee->SetCompany(companies.GetCorrectCompanyPosByConst(employee->GetCompanyId())->GetCompanyId());
    if (employee->GetCompanyId() ==
        companies.GetCorrectCompanyPosByConst(newEmployees.FindById(EmployeeId)->GetCompanyId())->GetCompanyId() ==
        false) {
        int x = 9;
    }
    Company *company = companies.GetCorrectCompanyPosByConst(employee->GetCompanyId());
    WTF();
    Company *test = companies.GetCorrectCompanyPosByConst(18);
    assert(company->GetCompanyEmployees()->check_is_valid());
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
    company->GetCompanyEmployees()->insert(SalaryId(employee->GetSalary(), EmployeeId), employee);
    WTF();
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
        Employee *employee = newEmployees.FindById(EmployeeId);
        employee->SetCompany(companies.GetCorrectCompanyPosByConst(employee->GetCompanyId())->GetCompanyId());
        assert(allEmployees.check_is_valid());
        if (newEmployees.FindById(EmployeeId)->GetSalary() == 0) {
            newEmployees.FindById(EmployeeId)->IncreaseGrade(BumpGrade);
            companies.GetCorrectCompanyPosByConst(
                    newEmployees.FindById(EmployeeId)->GetCompanyId())->IncreaseTotalGradesOfNewEmployees(BumpGrade);
            totalOfGradeOfNewEmployees += BumpGrade;
        } else {
            assert(allEmployees.check_is_valid());
            allEmployees.remove(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId));
            assert(allEmployees.check_is_valid());
            companies.GetCorrectCompanyPosByConst(
                    newEmployees.FindById(EmployeeId)->GetCompanyId())->GetCompanyEmployees()->remove(
                    SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId));
            newEmployees.FindById(EmployeeId)->IncreaseGrade(BumpGrade);
            allEmployees.insert(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId), employee);
            companies.GetCorrectCompanyPosByConst(
                    newEmployees.FindById(EmployeeId)->GetCompanyId())->GetCompanyEmployees()->insert(
                    SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId), employee);
        }
    }
    assert(allEmployees.check_is_valid());
    assert(companies.GetCorrectCompanyPosByConst(
            newEmployees.FindById(EmployeeId)->GetCompanyId())->GetCompanyEmployees()->check_is_valid());
    WTF();

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
            totalSum = companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees()->SumGrades(m);
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
    assert(companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees()->check_is_valid());
    WTF();

}

void HighTech::AverageBumpGradeBetweenSalaryByGroup(int CompanyId, int lowerSalary, int higherSalary,
                                                    double *averageBumpGrade) {
    if (averageBumpGrade == NULL || higherSalary < 0 || lowerSalary < 0 || higherSalary < lowerSalary ||
        CompanyId > companies.GetK() || CompanyId < 0) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    if (CompanyId != 0) {
        CompanyId = companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyId();
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
        totalAmount += companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees()->AmountMinMax(
                SalaryId(higherSalary, INT32_MAX), SalaryId(lowerSalary, 0));
        totalSum += companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees()->SumMinMax(
                SalaryId(higherSalary, INT32_MAX),
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
    if (*averageBumpGrade - (int) *averageBumpGrade < 1e-7) {
        std::cout << "AverageBumpGradeBetweenSalaryByGroup: " << *averageBumpGrade << ".0" << std::endl;
    } else {
        std::cout << "AverageBumpGradeBetweenSalaryByGroup: " << (double) ((int) (*averageBumpGrade * 10)) / 10.0
                  << std::endl;
    }
    assert(allEmployees.check_is_valid());
    if (CompanyId != 0) {
        assert(companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees()->check_is_valid());
    }
    WTF();

}

void HighTech::CompanyValue(int CompanyId, double *standing) {
    if (standing == NULL || CompanyId > companies.GetK() || CompanyId <= 0) {
        assert(allEmployees.check_is_valid());
        throw InvalidInput();
    }
    *standing = companies.GetCompanyValue(CompanyId); // O(log* k)
    // for test only
    if (*standing - (int) *standing < 1e-7) {
        std::cout << "CompanyValue: " << *standing << ".0" << std::endl;
    } else {
        std::cout << "CompanyValue: " << (int) ((*standing * 10)) / 10 << std::endl;
    }
    //

    assert(allEmployees.check_is_valid());
    if (companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees() != NULL) {
        assert(companies.GetCorrectCompanyPosByConst(CompanyId)->GetCompanyEmployees()->check_is_valid());

    }
    WTF();

}



//Extra

void HighTech::BumpGradeToEmployees(int lowerSalary, int higherSalary, int BumpGrade) {

}



