
#include "library2.h"
#include "HighTech.h"

void* init(int k)
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


StatusType addEmployee(void *DS, int EmployeeID, int CompanyID, int Grade) 
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

StatusType removeEmployee(void *DS, int EmployeeID) {
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

StatusType acquireCompany(void *DS, int AcquirerID, int TargetID, double Factor) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->AcquireCompany(AcquirerID, TargetID, Factor);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType employeeSalaryIncrease(void *DS, int EmployeeID, int SalaryIncrease)
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


StatusType promoteEmployee(void *DS, int EmployeeID, int BumpGrade) {
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

StatusType sumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int CompanyID, int m) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->SumOfBumpGradeBetweenTopWorkersByGroup(CompanyID, m);
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

StatusType averageBumpGradeBetweenSalaryByGroup(void *DS, int CompanyID, int lowerSalary, higherSalary) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->AverageBumpGradeBetweenSalaryByGroup(CompanyID, lowerSalary, higherSalary);
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

StatusType companyValue(void *DS, int CompanyID) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->CompanyValue(CompanyID);
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

StatusType bumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int BumpGrade)
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