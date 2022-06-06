
#include "library2.h"

#include "HighTech.h"

void *Init(int k)
{
	if (k <= 0)
	{
		return NULL;
	}
	else
	{
		HighTech *DS = new HighTech(k);
		return (void *) DS;
	}
}


StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Grade)
{
    if (DS == NULL) 
		return INVALID_INPUT;
    try {
        ((HighTech *) DS)->AddEmployee(EmployeeID, CompanyID, Grade);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}

StatusType RemoveEmployee(void *DS, int EmployeeID) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->RemoveEmployee(EmployeeID);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}

StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor)
{
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->AcquireCompany(companyID1, companyID2, factor);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType EmployeeSalaryIncrease(void *DS, int EmployeeID, int SalaryIncrease)
{
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->EmployeeSalaryIncrease(EmployeeID, SalaryIncrease);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
	catch(Failure) {
		return FAILURE;
	}
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType PromoteEmployee(void *DS, int EmployeeID, int BumpGrade) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->PromoteEmployee(EmployeeID, BumpGrade);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int CompanyID, int m, void* sumBumpGrade) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->SumOfBumpGradeBetweenTopWorkersByGroup(CompanyID, m, static_cast<int *>(sumBumpGrade));
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int CompanyID, int lowerSalary, int higherSalary, void* averageBumpGrade) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->AverageBumpGradeBetweenSalaryByGroup(CompanyID, lowerSalary, higherSalary,
                                                                static_cast<double *>(averageBumpGrade));
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType CompanyValue(void *DS, int companyID, void *standing)
{
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->CompanyValue(companyID, static_cast<double *>(standing));
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType BumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int BumpGrade)
{
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->BumpGradeToEmployees(lowerSalary, higherSalary, BumpGrade);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


void Quit(void **DS) {
    delete((HighTech*)*DS);
    *DS = NULL;
}