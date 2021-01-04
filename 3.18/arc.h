#pragma once

#include <iostream>
#include <string>
#include "constants.h"
#include "top.h"

struct Arc
{
    Top *fromTop;
    Top *toTop;
    int weight;
    Arc *next;
};

void deleteArcs(Arc *&arcs)
{
    Arc *curr = nullptr;
    while (arcs != nullptr)
    {
        curr = arcs;
        arcs = arcs->next;
        delete curr;
    }
}

void printArcs(Arc *arcs)
{
    if (arcs == nullptr)
    {
        std::cout << ARCS_EMPTY << std::endl;
        return;
    }
    std::cout << "ARCS: ";
    while (arcs != nullptr)
    {
        std::cout << "[" << arcs->fromTop->name << "]--" << arcs->weight << "-->[" << arcs->toTop->name << "] ";
        arcs = arcs->next;
    }
    std::cout << std::endl;
}

bool createArc(Top *&fromTop, Top *&toTop, int weight, Arc *&arcs)
{
    Arc *curr = arcs;
    Arc *prev = nullptr;
    while (curr != nullptr)
    {
        if ((curr->fromTop == fromTop) && (curr->toTop == toTop))
        {
            return false;
        }
        prev = curr;
        curr = curr->next;
    }
    curr = new Arc;
    curr->fromTop = fromTop;
    curr->toTop = toTop;
    curr->weight = weight;
    curr->next = nullptr;
    if (arcs == nullptr)
    {
        arcs = curr;
        return true;
    }
    prev->next = curr;
    return true;
}
