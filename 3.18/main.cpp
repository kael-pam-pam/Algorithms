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
#include <vector>
#include <regex>

const std::string FILE_PATH = "graph.txt";
const std::string GRAPH_LOADED = "Tree loaded from file " + FILE_PATH;
const std::string ERROR_FILE_IS_NOT_OPEN = "File is not open!";
const std::string ERROR_WRONG_FORMAT = "Wrong file format!";
const std::string ERROR_DOUBLE_ARC_DEFINITION = "Double arc definition!";
const std::string TOPS_EMPTY = "Tops is empty.";
const std::string ARCS_EMPTY = "Arcs is empty.";
const std::string ARCS_DELETED = "Arcs deleted.";
const std::string TOPS_DELETED = "Tops deleted.";
const std::string DATA_LOADED = "Data loaded from file " + FILE_PATH;
const std::string INPUT_TOPS_FOR_FIND_PATH = "Enter two tops (FROM and TO) through space: ";
const std::string OPERATION_CANCELED = "Operation canceled!";
const std::string FORMAT_FILE = "^([a-zA-Z]{1,})\\s([a-zA-Z]{1,})\\s([0-9]{1,})$";
const std::string FORMAT_INPUT_2_TOPS = "^([a-zA-Z]{1,})\\s([a-zA-Z]{1,})$";
const std::string MENU_TEXT = R"("====================== Task 3.18 ======================="
"========================================================"
"= Enter each command finish pressing button <Enter>.   ="
"=                                                      ="
"= Commands:                                            ="
"= `a` - load graph from file                           ="
"= `s` - print tops and arcs                            ="
"= `d` - find shortest path between tops                ="
"= `f` - delete tops and arcs                           ="
"=                                                      ="
"= `q` - close                                          ="
"========================================================")";

struct Top
{
    std::string name;
    int minWeight;
    bool needDetour;
    Top *next;
//    void *indexArc;
};

struct Arc
{
    Top *fromTop;
    Top *toTop;
    int weight;
    Arc *next;
};

struct MinPath
{
    Top toTopName;
    Arc *path;
    MinPath *next;
};

void deleteTops(Top *&tops)
{
    Top *curr = nullptr;
    if (tops == nullptr)
    {
        std::cout << TOPS_EMPTY << std::endl;
        return;
    }
    while (tops != nullptr)
    {
        curr = tops;
        tops = tops->next;
        delete curr;
    }
    std::cout << TOPS_DELETED << std::endl;
}

void deleteArcs(Arc *&arcs)
{
    Arc *curr = nullptr;
    if (arcs == nullptr)
    {
        std::cout << ARCS_EMPTY << std::endl;
        return;
    }
    while (arcs != nullptr)
    {
        curr = arcs;
        arcs = arcs->next;
        delete curr;
    }
    std::cout << ARCS_DELETED << std::endl;
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
        std::cout << "[" << arcs->fromTop->name << "]--" << arcs->weight << "--[" << arcs->toTop->name << "] ";
        arcs = arcs->next;
    }
    std::cout << std::endl;
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

Top* getTop(Top *tops, std::string elemName)
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
            if (!(fT->needDetour))
                std::cout << "[";
            std::cout << fT->minWeight;
            if (!(fT->needDetour))
                std::cout << "]";
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
        fromTop = getTop(tops, resultSearch[1]);
        toTop = getTop(tops, resultSearch[2]);
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

Top* createTop(Top *&tops, std::string elemName)
{
    Top *curr = nullptr;
    Top *prev = nullptr;
    curr = tops;
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
    if (tops == nullptr)
    {
        tops = curr;
        return tops;
    }
    prev->next = curr;
    return curr;
}

bool createArc(Top *&fromTop, Top *&toTop, int weight, Arc *&arcs)
{
    Arc *curr = nullptr;
    Arc *prev = nullptr;
    curr = arcs;
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

bool createTopsAndArcs(std::ifstream &finput, Top *&tops, Arc *&arcs)
{
    int lineNumber = 0, errorNumber = 0;
    std::string inputFile;
    std::smatch resultSearch;
    const std::regex searchData(FORMAT_FILE);
    Top *fromTop = nullptr;
    Top *toTop = nullptr;
    while (getline(finput, inputFile))
    {
        lineNumber++;
        if (std::regex_match(inputFile, resultSearch, searchData))
        {
            fromTop = createTop(tops, resultSearch[1]);
            toTop = createTop(tops, resultSearch[2]);
            if (!(createArc(fromTop, toTop, std::stoi(resultSearch[3]), arcs)))
            {
                errorNumber = 1;
            }
        }
        else
        {
            errorNumber = 2;
        }
        if (errorNumber != 0)
        {   
            switch (errorNumber)
            {
                case 1:
                    std::cout << "Line [" << lineNumber << "]: " << ERROR_DOUBLE_ARC_DEFINITION << std::endl;
                    break;
                case 2:
                    std::cout << "Line [" << lineNumber << "]: " << ERROR_WRONG_FORMAT << std::endl;
                    break;
            }
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
    {
        std::cout << DATA_LOADED << std::endl;
    }
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
    //std::vector<std::string> tops;
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
                deleteTops(headTop);
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
