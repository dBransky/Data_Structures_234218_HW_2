
#include "HighTech.h"



// in C need to check that k > 0...
HighTech::HighTech(int k) : amountOfNewEmployees(0), totalOfGradeOfNewEmployees(0), amountOfEmployeesWithSalaryBiggerThenZero(0), companies(k), allEmployees(), newEmployees() {}

HighTech::~HighTech()
{
    companies.FreeAll();
    newEmployees.FreeAll();
}

void HighTech::AddEmployee(int EmployeeId, int CompanyId, int Grade)
{
    if (EmployeeId <= 0 || CompanyId <= 0 || CompanyId > companies.GetK() || Grade < 0)
    {
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) != NULL)
    {
        throw Failure();
    }
    int correctCompanyId = companies.Find(CompanyId); // O(log* k)
    newEmployees.Insert(new Employee(EmployeeId, Grade, 0, correctCompanyId));
    Company* company = companies.GetCompany(CompanyId);
    company->IncreaseAmountOfNewEmployees(1);
    company->IncreaseTotalGradesOfNewEmployees(Grade);
    amountOfNewEmployees++;
    totalOfGradeOfNewEmployees += Grade;
}

void HighTech::RemoveEmployee(int EmployeeId)
{
    if (EmployeeId <= 0)
    {
        throw InvalidInput();
    }
    Employee* employee = newEmployees.FindById(EmployeeId);
    if (employee == NULL)
    {
        throw Failure();
    }
    if (employee->IsSalaryBiggerThanZero())
    {
        allEmployees.remove(SalaryId(employee->GetSalary(), EmployeeId));//log n
        int correctCompany = companies.Find(employee->GetCompanyId());
        companies.GetCompany(employee->GetCompanyId())->GetCompanyEmployees().remove(SalaryId(employee->GetSalary(), EmployeeId));
    }
    else
    {
        Company* company = companies.GetCompany(employee->GetCompanyId());
        company->IncreaseAmountOfNewEmployees(-1);
        company->IncreaseTotalGradesOfNewEmployees(employee->GetGrade() * (-1));
        amountOfNewEmployees--;
        totalOfGradeOfNewEmployees -= employee->GetGrade();
    }
    newEmployees.DeleteById(EmployeeId);
}

void HighTech::AcquireCompany(int AcquireId, int TargetId, double Factor)
{
    if (AcquireId <= 0 || AcquireId > companies.GetK() || TargetId <= 0 || TargetId > companies.GetK())
    {
        throw InvalidInput();
    }
    if (companies.Find(AcquireId) == companies.Find(TargetId) || Factor <= 0.0)
    {
        throw InvalidInput();
    }
    Company* AcquireCompany = companies.GetCompany(AcquireId);
    Company* TargetCompany = companies.GetCompany(TargetId);
    int amountOfEmployees = TargetCompany->GetCompanyAmountOfEmployees();
    int amountOfNewEmployees = TargetCompany->GetAmountOfNewEmployees();
    int totalGrades = TargetCompany->GetTotalGradeOfNewEmployees();
    AcquireCompany->GetCompanyEmployees().merge(TargetCompany->GetCompanyEmployees());
    AcquireCompany->IncreaseAmountOfEmployees(amountOfEmployees);
    AcquireCompany->IncreaseAmountOfNewEmployees(amountOfNewEmployees);
    AcquireCompany->IncreaseTotalGradesOfNewEmployees(totalGrades);
    Pair<Employee*, SalaryId>* pair_list = companies.GetCompany(AcquireId)->GetCompanyEmployees().GetFirstNum(AcquireCompany->GetCompanyAmountOfEmployees());
    for (int i = 0; i < AcquireCompany->GetCompanyAmountOfEmployees(); i++)
    {
        pair_list[i].element->SetCompany(AcquireId);
        pair_list[i].element = NULL;
    }
    companies.Union(companies.Find(AcquireId), companies.Find(TargetId), Factor);
}

void HighTech::EmployeeSalaryIncrease(int EmployeeId, int SalaryIncrease)
{
    if (EmployeeId <= 0 || SalaryIncrease <= 0)
    {
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) == NULL)
    {
        throw Failure();
    }
    int companyId = newEmployees.FindById(EmployeeId)->GetCompanyId();
    Employee* employee = newEmployees.FindById(EmployeeId);
    if (employee->GetSalary() != 0)
    {
        allEmployees.remove(SalaryId(employee->GetSalary(), EmployeeId));
        companies.GetCompanyById(companyId)->GetCompanyEmployees().remove(SalaryId(employee->GetSalary(), EmployeeId));
    }
    else
    {
        amountOfEmployeesWithSalaryBiggerThenZero++;
        companies.GetCompanyById(companyId)->IncreaseAmountOfEmployees(1);
        companies.GetCompanyById(companyId)->IncreaseTotalGradesOfNewEmployees(-1);
        companies.GetCompanyById(companyId)->IncreaseTotalGradesOfNewEmployees(-1 * employee->GetGrade());
        amountOfNewEmployees--;
        totalOfGradeOfNewEmployees -= employee->GetSalary();
    }
    newEmployees.FindById(EmployeeId)->IncreaseSalary(SalaryIncrease);
    allEmployees.insert(SalaryId(employee->GetSalary(), EmployeeId), employee);
    companies.GetCompanyById(companyId)->GetCompanyEmployees().insert(SalaryId(employee->GetSalary(), EmployeeId), employee);
}

void HighTech::PromoteEmployee(int EmployeeId, int BumpGrade)
{
    if (EmployeeId <= 0)
    {
        throw InvalidInput();
    }
    if (newEmployees.FindById(EmployeeId) == NULL)
    {
        throw Failure();
    }
    if (BumpGrade > 0)
    {
        newEmployees.FindById(EmployeeId)->IncreaseGrade(1);
        if (newEmployees.FindById(EmployeeId)->GetSalary() == 0)
        {
            companies.GetCompanyById(newEmployees.FindById(EmployeeId)->GetCompanyId())->IncreaseTotalGradesOfNewEmployees(1);
            totalOfGradeOfNewEmployees++;
            companies.GetCompanyById(newEmployees.FindById(EmployeeId)->GetCompanyId())->GetCompanyEmployees().UpdateGrades(SalaryId(newEmployees.FindById(EmployeeId)->GetSalary(), EmployeeId));

        }
    }
}

void HighTech::SumOfBumpGradeBetweenTopWorkersByGroup(int CompanyId, int m, int *sumBumpGrade)
{
    if (sumBumpGrade == NULL || m <= 0 || CompanyId < 0 || CompanyId > companies.GetK())
    {
        throw InvalidInput();
    }
    int totalSum = 0;
    if (CompanyId > 0)
    {
        if (companies.GetCompany(CompanyId)->GetCompanyAmountOfEmployees() < m)
        {
            throw Failure();
        }
        else
        {
            totalSum = companies.GetCompany(CompanyId)->GetCompanyEmployees().SumGrades(m);
        }
    }
    else
    {
        if (amountOfEmployeesWithSalaryBiggerThenZero < m)
        {
            throw Failure();
        }
        else
        {
            totalSum = allEmployees.SumGrades(m);
        }
    }
    *sumBumpGrade = totalSum;
    std::cout << "SumOfBumpGradeBetweenTopWorkersByGroup: " << ((int)*sumBumpGrade)  << std::endl;
}

void HighTech::AverageBumpGradeBetweenSalaryByGroup(int CompanyId, int lowerSalary, int higherSalary, double *averageBumpGrade)
{
    if (averageBumpGrade == NULL || higherSalary < 0 || lowerSalary < 0 || higherSalary < lowerSalary || CompanyId > companies.GetK() || CompanyId < 0)
    {
        throw InvalidInput();
    }
    double totalSum = 0.0;
    double totalAmount = 0.0;
    if (lowerSalary == 0)
    {
        if (CompanyId == 0)
        {
            totalSum += totalOfGradeOfNewEmployees;
            totalAmount += amountOfNewEmployees;
        }
        else
        {
            totalSum += companies.GetCompany(CompanyId)->GetTotalGradeOfNewEmployees();
            totalAmount += companies.GetCompany(CompanyId)->GetAmountOfNewEmployees();
        }
    }
    if (CompanyId > 0)
    {
        totalAmount += companies.GetCompany(CompanyId)->GetCompanyEmployees().AmountMinMax(SalaryId(higherSalary,INT16_MAX),SalaryId(lowerSalary, INT16_MIN));
        totalSum += companies.GetCompany(CompanyId)->GetCompanyEmployees().SumMinMax(SalaryId(higherSalary,INT16_MAX),SalaryId(lowerSalary, INT16_MIN));
        if (totalAmount == 0)
        {
            throw Failure();
        }
    }
    else
    {
        totalAmount += allEmployees.AmountMinMax(SalaryId(higherSalary,INT16_MAX),SalaryId(lowerSalary, INT16_MIN));
        totalSum += allEmployees.SumMinMax(SalaryId(lowerSalary, INT16_MIN), SalaryId(higherSalary,INT16_MAX));
        if (totalAmount == 0)
        {
            throw Failure();
        }
    }
    *averageBumpGrade = totalSum / totalAmount;
    std::cout << "AverageBumpGradeBetweenSalaryByGroup: " << ((double)*averageBumpGrade + 0.0)  << std::endl;
}

void HighTech::CompanyValue(int CompanyId, double *standing)
{
    if (standing == NULL || CompanyId > companies.GetK() || CompanyId <= 0)
    {
        throw InvalidInput();
    }
    *standing = companies.GetCompanyValue(CompanyId); // O(log* k)
    std::cout << "CompanyValue: " << *standing << std::endl;
}


//Extra

void HighTech::BumpGradeToEmployees(int lowerSalary, int higherSalary, int BumpGrade)
{

}



