#pragma once

struct Top
{
    std::string name;
    int minWeight;
    bool needDetour;
    Top *next;
    void *indexArc;
    void *pathArc;
};

void deleteTops(Top *&tops)
{
    Top *curr = nullptr;
    while (tops != nullptr)
    {
        curr = tops;
        tops = tops->next;
        delete curr;
    }
}

void printTops(Top *tops)
{
    if (tops == nullptr)
    {
        std::cout << TOPS_EMPTY << std::endl;
        return;
    }
    std::cout << "TOPS: ";
    while (tops != nullptr)
    {
        std::cout << "[" << tops->name << "] ";
        tops = tops->next;
    }
    std::cout << std::endl;
}

Top* getTopByName(Top *tops, std::string elemName)
{
    Top *curr = tops;
    while (curr != nullptr)
    {
        if (curr->name == elemName)
        {
            return curr;
        }
        curr = curr->next;
    }
    return curr;    
}

Top* createTop(Top *&tops, std::string elemName)
{
    Top *curr = tops;
    Top *prev = nullptr;
    while (curr != nullptr)
    {
        if (curr->name == elemName)
        {
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }
    curr = new Top;
    curr->name = elemName;
    curr->minWeight = INT_MAX;
    curr->needDetour = true;
    curr->next = nullptr;
    curr->indexArc = nullptr;
    curr->pathArc = nullptr;
    if (tops == nullptr)
    {
        tops = curr;
        return tops;
    }
    prev->next = curr;
    return curr;
}

void printTopsMinWeight(Top *tops)
{
    Top *fT = tops;
    while (fT != nullptr)
    {     
        std::cout << "    "; 
        if (fT->minWeight == INT_MAX)
        {
            std::cout << "INF";
        }
        else
        {
            if (!(fT->needDetour)) std::cout << "[";
            std::cout << fT->minWeight;
            if (!(fT->needDetour)) std::cout << "]";
        }
        fT = fT->next;
    }
    std::cout << std::endl;
}

Top* getTopWithMinestWeight(Top *&tops)
{
    Top *curr = tops;
    Top *minest = nullptr;
    while (curr != nullptr)
    {
        if (curr->needDetour == true)
        {
            if ((minest == nullptr) || (minest->minWeight > curr->minWeight))
                minest = curr;
        }
        curr = curr->next;
    }
    return minest;  
}
