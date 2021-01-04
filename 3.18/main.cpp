/* условия задачи:
    Задача 3.18
    Реализовать алгоритм поиска кратчайших путей Дейкстры и
    проиллюстрировать по шагам этапы его выполнения (10)
*/

// Среда разработки: VS Code. C/C++
// Compiler: mingw64 g++

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "constants.h"
#include "top.h"
#include "arc.h"

struct MinPath
{
    Top toTopName;
    Arc *path;
    MinPath *next;
};


void calc(Top *&tops, Arc *&arcs, Top *mT)
{
    Arc *curr = arcs;
    while (curr != nullptr)
    {
        if (curr->fromTop == mT)
        {
            if ((curr->toTop->needDetour != false) &&
            (curr->weight + mT->minWeight < curr->toTop->minWeight))
                curr->toTop->minWeight = curr->weight + mT->minWeight;
        }
        curr = curr->next;
    }
}

void algorithmDijkstra(Top *&tops, Arc *&arcs, Top *&fromTop, Top *&toTop)
{
    Top *fT = tops;
    while (fT != nullptr)
    {
        fT->needDetour = true;
        fT->minWeight = INT_MAX;
        fT = fT->next;
    }

    fT = tops;
    while (fT != nullptr)
    {
        std::cout << "    [" << fT->name << "]";
        fT = fT->next;
    }
    std::cout << std::endl;
    
    Top* mT = fromTop;
    fromTop->minWeight = 0;
    fromTop->needDetour = false;
    printTopsMinWeight(tops);
    calc(tops, arcs, mT);
    printTopsMinWeight(tops);

    mT = getTopWithMinestWeight(tops);
    mT->needDetour = false;
    printTopsMinWeight(tops);
    calc(tops, arcs, mT);
    printTopsMinWeight(tops);

    mT = getTopWithMinestWeight(tops);
    mT->needDetour = false;
    printTopsMinWeight(tops);
    calc(tops, arcs, mT);
    printTopsMinWeight(tops);

    mT = getTopWithMinestWeight(tops);
    mT->needDetour = false;
    printTopsMinWeight(tops);
    calc(tops, arcs, mT);
    printTopsMinWeight(tops);

    mT = getTopWithMinestWeight(tops);
    mT->needDetour = false;
    printTopsMinWeight(tops);
    calc(tops, arcs, mT);
    printTopsMinWeight(tops);
}

void findShortestPath(Top *&tops, Arc *&arcs)
{
    Top *fromTop = nullptr;
    Top *toTop = nullptr;
    std::string inputTops;

    printTops(tops);
    if (tops == nullptr)
    {
        std::cout << OPERATION_CANCELED << std::endl;
        return;
    }
    std::cin.ignore(32767, '\n'); 
    std::cout << INPUT_TOPS_FOR_FIND_PATH;
    std::getline(std::cin, inputTops);

    std::smatch resultSearch;
    const std::regex searchData(FORMAT_INPUT_2_TOPS);

    if (std::regex_match(inputTops, resultSearch, searchData))
    {
        fromTop = getTopByName(tops, resultSearch[1]);
        toTop = getTopByName(tops, resultSearch[2]);
        if ((fromTop == nullptr) || (toTop == nullptr))
        {
            std::cout << "Input top is not exists!" << std::endl;
            return;
        }
        if (fromTop == toTop)
        {
            std::cout << "FROM and TO tops must be not equal!" << std::endl;
            return;
        }
        algorithmDijkstra(tops, arcs, fromTop, toTop);
        return;
    }
    std::cout << "Wrong input format!" << std::endl;
    return;
}


bool createTopsAndArcs(std::ifstream &finput, Top *&tops, Arc *&arcs)
{
    int lineNumber = 0, errorNumber = 0;
    std::string inputFile;
    std::smatch resultSearch;
    const std::regex searchDataEQ(FORMAT_FILE_EQ);
    const std::regex searchDataTO(FORMAT_FILE_TO);
    const std::regex searchDataFR(FORMAT_FILE_FR);
    Top *fromTop = nullptr, *toTop = nullptr;
    while (getline(finput, inputFile))
    {
        lineNumber++;
        if (std::regex_match(inputFile, resultSearch, searchDataEQ))
        {
            fromTop = createTop(tops, resultSearch[1]);
            toTop = createTop(tops, resultSearch[2]);
            if (!(createArc(fromTop, toTop, std::stoi(resultSearch[3]), arcs)) || !(createArc(toTop, fromTop, std::stoi(resultSearch[3]), arcs)))
                errorNumber = 1;
        }
        else if (std::regex_match(inputFile, resultSearch, searchDataTO))
        {
            fromTop = createTop(tops, resultSearch[1]);
            toTop = createTop(tops, resultSearch[2]);
            if (!(createArc(toTop, fromTop, std::stoi(resultSearch[3]), arcs)))
                errorNumber = 1;
        }
        else if (std::regex_match(inputFile, resultSearch, searchDataFR))
        {
            fromTop = createTop(tops, resultSearch[1]);
            toTop = createTop(tops, resultSearch[2]);
            if (!(createArc(fromTop, toTop, std::stoi(resultSearch[3]), arcs)))
                errorNumber = 1;
        }
        else
            errorNumber = 2;
        if (errorNumber != 0)
        {   
            if (errorNumber == 1)
                std::cout << "Line [" << lineNumber << "]: " << ERROR_DOUBLE_ARC_DEFINITION << std::endl;
            if (errorNumber == 2)
                std::cout << "Line [" << lineNumber << "]: " << ERROR_WRONG_FORMAT << std::endl;
            return false;
        }        
    }
    return true;
}

void loadGraphFromFile(Top *&tops, Arc *&arcs)
{
    std::ifstream fin;
    fin.open(FILE_PATH);
    if (!fin)
    {
       std::cout << ERROR_FILE_IS_NOT_OPEN << std::endl;
       return;
    }
    if (createTopsAndArcs(fin, tops, arcs))
        std::cout << DATA_LOADED << std::endl;
    fin.close();  
}

void showMainMenu()
{
    system("cls");
    std::cout << MENU_TEXT << std::endl;
}

void mainMenu()
{
    char inputKey;   
    Top *headTop = nullptr;
    Arc *headArc = nullptr;

    showMainMenu();
    do
    {
        std::cout << "Enter command: ";
        std::cin >> inputKey;
        switch (inputKey) {
            case 'a':
                deleteArcs(headArc);
                deleteTops(headTop);
                loadGraphFromFile(headTop, headArc);
                break;
            case 's':
                printTops(headTop);
                printArcs(headArc);
                break;
            case 'd': 
                findShortestPath(headTop, headArc);
                break;
            case 'f':
                deleteArcs(headArc);
                std::cout << ARCS_DELETED << std::endl;
                deleteTops(headTop);
                std::cout << TOPS_DELETED << std::endl;
                break;
        }
    } 
    while (inputKey != 'q');
    deleteArcs(headArc);
    deleteTops(headTop);
}

int main()
{
    mainMenu();
}
