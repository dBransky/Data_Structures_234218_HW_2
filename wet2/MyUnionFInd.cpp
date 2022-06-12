#include "MyUnionFind.h"

UnionFind::UnionFind(int k)
{
    K = k;
    size = new int[k];
    parents = new int[k];
    salaryIncrease = new double[k];
    elements = new Company*[k];
    for (int i = 0; i < k; i++)
    {
        size[i] = 1;
        parents[i] = -1;
        salaryIncrease[i] = 0.0;
        elements[i] = new Company(i + 1);
    }
}

UnionFind::~UnionFind()
{
    delete[] size;
    delete[] parents;
    delete[] salaryIncrease;
    for (int i = 0; i < K; i++)
    {
        if (elements[i] != NULL)
        {
            delete elements[i];
        }
    }
    delete[] elements;
}

double UnionFind::GetCompanyValue(int CompanyId)
{
    if (elements[CompanyId - 1]->GetCompanyValue() == 0)
    {
        int x = 5;
    }
    double sum = (elements[CompanyId - 1]->GetCompanyValue()) + salaryIncrease[CompanyId - 1];
    int last = CompanyId;
    while (last != -1)
    {
        last = parents[last - 1];
        if (last != -1)
        {
            sum += salaryIncrease[last - 1];
        }
    }
    return sum;
}

int UnionFind::Find(int CompanyId)
{
    int temp = CompanyId;
    int last = CompanyId;
    double sumR = 0;
    while (last != -1)
    {
        temp = last;
        last = parents[last - 1];
        if (last != -1)
        {
            sumR += salaryIncrease[temp - 1];
        }
    }
    int targetCompany = temp;
    last = CompanyId;
    double save = 0.0;
    while (last != -1 && targetCompany != CompanyId)
    {
        temp = last;
        last = parents[last - 1];
        if (last != -1 && last != targetCompany)
        {
            parents[temp - 1] = targetCompany;
            save = sumR - salaryIncrease[temp - 1];
            salaryIncrease[temp - 1] = sumR;
            sumR = save;

        }
    }
    return targetCompany;
}

Company* UnionFind::GetCorrectCompanyPosByConst(int CompanyId)
{
    return elements[Find(CompanyId) - 1];
}

void UnionFind::Union(int acquire, int target, double Factor)
{
    int realAcquire = Find(acquire);
    int realTarget = Find(target);
    long long amountToAdd = GetCompanyValue(realTarget) * Factor;
    parents[Find(realTarget) - 1] = realAcquire;
    salaryIncrease[realTarget - 1] = salaryIncrease[realTarget - 1] - amountToAdd - salaryIncrease[realAcquire - 1];
    salaryIncrease[realAcquire - 1] += amountToAdd;
}


int UnionFind::GetK()
{
    return K;
}
