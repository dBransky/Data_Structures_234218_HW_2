
#include "MyUnionFind.h"

UnionFind::UnionFind(int k)
{
    K = k;
    size = new int[k];
    parents = new int[k];
    elements = new Company*[k];
    for (int i = 0; i < k; i++)
    {
        size[i] = 1;
        parents[i] = -1;
        elements[i] = new Company(i + 1);
    }
}

int UnionFind::Find(int CompanyId)
{
    int temp = CompanyId;
    int last = CompanyId;
    while (last != -1)
    {
        temp = last;
        last = parents[last - 1];
    }
    int targetCompany = temp;
    last = CompanyId;
    while (last != -1)
    {
        temp = last;
        last = parents[last - 1];
        if (last != -1)
        {
            parents[temp - 1] = targetCompany;
        }
    }
    return targetCompany;
}

Company* UnionFind::GetCompany(int CompanyId)
{
    return elements[CompanyId - 1];
}

void UnionFind::Union(int acquire, int target, double Factor)
{
    double amountToAdd = elements[target - 1]->GetCompanyValue() * Factor;
    for (int i = 0; i < K; i++)
    {
        if (Find(i + 1) == acquire)
        {
            elements[i]->IncreaseValue(amountToAdd);
        }
    }
    parents[Find(target) - 1] = acquire;
}

void UnionFind::Itamar(int companyId, int value)
{
    elements[companyId - 1]->SetTotalValue(value);
}


int UnionFind::GetK()
{
    return K;
}

void UnionFind::PrintStatus()
{
    std::cout << " ---------------------------------- " << std::endl << "  ";
    for (int i = 1; i <= K ; i++)
    {
        std::cout << i << "   ";
    }
    std::cout << std::endl << "[ ";
    for (int i = 0; i < K - 1; i++)
    {
        if (parents[i] == -1)
            std::cout << parents[i] << ", ";
        else
        {
            std::cout << parents[i] << ",  ";
        }
    }
    std::cout << parents[K - 1] << "]" << std::endl;

    std::cout << std::endl << "[ ";
    for (int i = 0; i < K - 1; i++)
    {
        std::cout << elements[i]->GetCompanyValue() << ",  ";
    }
    std::cout << elements[K - 1]->GetCompanyValue() << "]" << std::endl;
    std::cout << " ---------------------------------- " << std::endl << " ";
}