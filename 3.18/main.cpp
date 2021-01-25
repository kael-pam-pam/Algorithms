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

bool calc(Top *mT)
{
    Arc *curr = static_cast<Arc*>(mT->indexArc);
    bool hasChanges = false; 
    std::cout << "--CHANGES: ";
    while ((curr != nullptr) && (curr->fromTop == mT))
    {
        if ((curr->toTop->needDetour != false) &&
            (curr->weight + mT->minWeight < curr->toTop->minWeight))
        {
            curr->toTop->minWeight = curr->weight + mT->minWeight;
            curr->toTop->path.clear();
            curr->toTop->path.push_back(mT->name);
            hasChanges = true;
            std::cout << curr->toTop->name << "(" << mT->name << ") ";
        }
        curr = curr->next;
    }
    std::cout << std::endl;
    return hasChanges;
}

void algorithmDijkstra(Top *&tops, Arc *&arcs, Top *&fromTop, Top *&toTop)
{
    //инициализация
    Top *fT = tops;
    while (fT != nullptr)
    {
        fT->needDetour = true;
        fT->minWeight = INT_MAX;
        fT = fT->next;
    }

    //вывод заголовка
    fT = tops;
    while (fT != nullptr)
    {
        std::cout << "[" << fT->name << "]\t";
        fT = fT->next;
    }
    std::cout << std::endl;
    std::cout << "---" << std::endl;
    
    //точка входа
    Top* mT = fromTop;
    mT->minWeight = 0;
    do
    {
        mT->needDetour = false;

        if (mT->path.size() != 0)
        {
            Top *t = getTopByName(tops, mT->path[0]);
            mT->path.clear();
            for (int i = 0; i < t->path.size(); i++)
            {
                mT->path.push_back(t->path[i]);
            }
            mT->path.push_back(t->name);
        }

        printTopsMinWeight(tops);
        calc(mT);
        printTopsMinWeight(tops);
        mT = getTopWithMinestWeight(tops);
    } while ((mT != nullptr) && (mT != toTop));  

    if ((mT != nullptr) && (mT->path.size() != 0))
    {
        Top *t = getTopByName(tops, mT->path[0]);
        mT->path.clear();
        for (int i = 0; i < t->path.size(); i++)
        {
            mT->path.push_back(t->path[i]);
        }
        mT->path.push_back(t->name);
    }

    std::cout << std::endl << "Path from [" << fromTop->name << "] to [" << toTop->name << "]: ";
    if (toTop->path.size() == 0)
    {
        std::cout << "NO PATH" << std::endl;
    } 
    else 
    {
        for (int i = 0; i < toTop->path.size(); i++)
        {
            std::cout << "[" << toTop->path[i] << "]->";
        }
        std::cout << "[" << toTop->name << "]" << std::endl;
    }
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
            std::cout << ERROR_TOP_NOT_EXISTS << std::endl;
            return;
        }
        if (fromTop == toTop)
        {
            std::cout << ERROR_FROM_TO_EQUAL << std::endl;
            return;
        }
        algorithmDijkstra(tops, arcs, fromTop, toTop);
        return;
    }
    std::cout << ERROR_WRONG_INPUT_FORMAT << std::endl;
    return;
}


bool createTopsAndArcs(std::ifstream &finput, Top *&tops, Arc *&tailArc, Arc *&arcs)
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
            if (!(createArc(fromTop, toTop, std::stoi(resultSearch[3]), arcs, tailArc)) || !(createArc(toTop, fromTop, std::stoi(resultSearch[3]), arcs, tailArc)))
                errorNumber = 1;
        }
        else if (std::regex_match(inputFile, resultSearch, searchDataTO))
        {
            fromTop = createTop(tops, resultSearch[1]);
            toTop = createTop(tops, resultSearch[2]);
            if (!(createArc(toTop, fromTop, std::stoi(resultSearch[3]), arcs, tailArc)))
                errorNumber = 1;
        }
        else if (std::regex_match(inputFile, resultSearch, searchDataFR))
        {
            fromTop = createTop(tops, resultSearch[1]);
            toTop = createTop(tops, resultSearch[2]);
            if (!(createArc(fromTop, toTop, std::stoi(resultSearch[3]), arcs, tailArc)))
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

void loadGraphFromFile(Top *&tops, Arc *&tailArc, Arc *&arcs)
{
    std::ifstream fin;
    fin.open(FILE_PATH);
    if (!fin)
    {
       std::cout << ERROR_FILE_IS_NOT_OPEN << std::endl;
       return;
    }
    if (createTopsAndArcs(fin, tops, tailArc, arcs))
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
    Arc *headArc = nullptr, *tailArc = nullptr;

    showMainMenu();
    do
    {
        std::cout << "Enter command: ";
        std::cin >> inputKey;
        switch (inputKey) {
            case 'a':
                deleteArcs(headArc);
                deleteTops(headTop);
                loadGraphFromFile(headTop, tailArc, headArc);
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
