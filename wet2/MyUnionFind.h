#include "MyHashTable.h"
class ReverseTree;

class RootDetails
{
private:
    Company* company;
    ReverseTree* head;

public:
    explicit RootDetails(Company* initCompany)
    {
        company = initCompany;
    }
    int GetAmountOfEmployees()
    {
        return company->GetCompanyAmountOfEmployees();
    }
    int GetCompanyId()
    {
        return company->GetCompanyId();
    }
    Company* GetCompanyInfo()
    {
        return company;
    }
    ReverseTree* GetHead() { return head; }
};


class ReverseTree
{
private:
    Employee* value;
    ReverseTree* father;
    RootDetails* details; // only if father == NULL

public:
    ReverseTree(Employee* employee) : value(employee), father(nullptr) {};
    ReverseTree(Employee* employee, ReverseTree* father) : value(employee), father(father) {};

    Employee* GetEmployeeValue() { return value; }
    ReverseTree* GetFather() { return father; }
    RootDetails* GetRootDetails() { return details; }
    void DeleteRootDetails() { delete(details); details = NULL; }
    void SetFather(ReverseTree* newFather) { father = newFather; }
};


class UnionFind
{
private:
        int AmountOfCompanies;
        RootDetails** CompaniesArray;
        HashTable employees;

public:
    UnionFind(int k)
    {
        AmountOfCompanies = k;
        CompaniesArray = new RootDetails*[k];
    }

    void Union(int acquire, int target, double factor)
    {
        ReverseTree* acquireTree = CompaniesArray[acquire - 1]->GetHead();
        ReverseTree* targetTree = CompaniesArray[target- 1]->GetHead();
        targetTree->SetFather(acquireTree);
        targetTree->DeleteRootDetails();
        CompaniesArray[acquire - 1]->GetCompanyInfo()->IncreaseAmountOfEmployees(CompaniesArray[target- 1]->GetCompanyInfo()->GetCompanyAmountOfEmployees());
        RootDetails* toDelete = CompaniesArray[acquire - 1];
        CompaniesArray[target - 1] = CompaniesArray[acquire - 1];
        delete(toDelete);
    }


};
