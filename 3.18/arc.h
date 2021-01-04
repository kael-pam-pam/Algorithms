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

bool createArc(Top *&fromTop, Top *&toTop, int weight, Arc *&arcs, Arc *&tailArc)
{
    Arc *curr;
    if (fromTop->indexArc == nullptr)
    {
        curr = new Arc;
        curr->fromTop = fromTop;
        curr->toTop = toTop;
        curr->weight = weight;
        curr->next = nullptr;

        fromTop->indexArc = curr;

        if (arcs == nullptr)
        {
            arcs = curr;
            tailArc = curr;
        }
        else
        {
           tailArc->next = curr;
           tailArc = curr;
        }
        return true;
    } 
    else
    {
        curr = static_cast<Arc*>(fromTop->indexArc);
        Arc *prev = nullptr, *newest = nullptr;
        while ((curr != nullptr) && (curr->fromTop == fromTop))
        {
            if ((curr->fromTop == fromTop) && (curr->toTop == toTop))
            {
                return false;
            }
            prev = curr;
            curr = curr->next;
        }
        newest = new Arc;
        newest->fromTop = fromTop;
        newest->toTop = toTop;
        newest->weight = weight;
        newest->next = prev->next;
        prev->next = newest;
        if (curr == nullptr)
            tailArc = newest;
        return true;
    }
}
