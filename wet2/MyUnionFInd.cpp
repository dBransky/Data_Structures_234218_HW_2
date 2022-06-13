#include "MyUnionFind.h"


UnionFind::UnionFind(int k)
{
    K = k;
    size = new int[k];
    parents = new int[k];
    salaryIncrease = new double[k];
    owners = new int[k];
    elements = new Company*[k];
    for (int i = 0; i < k; i++)
    {
        owners[i] = -1;
        size[i] = 1;
        parents[i] = -1;
        salaryIncrease[i] = 0.0;
        elements[i] = new Company(i + 1);
    }
}

UnionFind::~UnionFind()
{
    delete[] size;
    delete[] owners;
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
        int ownerCompany;
        last = CompanyId;
        ownerCompany = last;
        while (last != -1)
        {
            ownerCompany = last;
            last = owners[last - 1];
        }
        last = CompanyId;
        while (last != -1)
        {
            temp = last;
            last = owners[last - 1];
            if (last != -1)
            {
                owners[temp - 1] = ownerCompany;
            }
        }
        return ownerCompany;
    }

Company* UnionFind::GetCorrectCompanyPosByConst(int CompanyId)
{
    return elements[Find(CompanyId) - 1];
}

void UnionFind::Union(int acquire, int target, double Factor)
{
    acquire = Find(acquire);
    target = Find(target);
    double value = Factor * GetCompanyValue(target);
    if (size[target - 1] <= size[acquire - 1])
    {
        int temp, last = acquire;
        while (last != -1)
        {
            temp = last;
            last = parents[temp - 1];
            if (last != -1)
            {
            //    elements[last - 1]->IncreaseValue(-1 * value);
            }
        }
        int temp2, last2 = target;
        while (last2 != -1)
        {
            temp2 = last2;
            last2 = parents[temp2 - 1];
        }
        salaryIncrease[temp - 1] += value;
        salaryIncrease[temp2 - 1] -= salaryIncrease[temp - 1];
        parents[temp2 - 1] = temp;
    }
    else
    {
        int temp, last = acquire;
        while (last != -1)
        {
            temp = last;
            last = parents[temp - 1];
        }
        int temp2, last2 = target;
        while (last2 != -1)
        {
            temp2 = last2;
            last2 = parents[temp2 - 1];
        }
        salaryIncrease[temp - 1] += value - salaryIncrease[temp2 - 1];
        parents[temp - 1] = temp2;
    }
    size[acquire - 1] += size[target - 1];
    owners[target - 1] = acquire;
}


int UnionFind::GetK()
{
    return K;
}
