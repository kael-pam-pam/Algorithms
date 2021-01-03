/* условия задачи:
    Задача 2.7
    Структура некоторого института задана деревом. Сыновьям корневой вершины
    соответствуют факультеты, факультеты в свою очередь делятся на кафедры,
    которые могут иметь филиалы. Листьям дерева соответствуют преподаватели.
    Выявить преподавателей, ведущих занятия на трех и более кафедрах (10).
*/

// Среда разработки: VS Code. C/C++
// Compiler: mingw64 g++

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdio.h>

const int DEPTH_UNIVERSITY = 0;
const int DEPTH_INSTITUTE = 1;
const int DEPTH_DEPARTMENT = 2;
const int DEPTH_BRANCH = 3;
const int DEPTH_TEACHER = 4;
const std::string FORMAT_SEARCH_CHILDS = "^(\\*{1,})\\s(.*)$";
const std::string FORMAT_SEARCH_HEAD = "^(.*)$";
const std::string SPACES = "  ";
const std::string FILE_PATH = "test_tree.txt";
const std::string TREE_LOADED = "Tree loaded from file " + FILE_PATH;
const std::string DELETE_OLD_TREE = "Delete old tree...";
const std::string DELETED_OLD_TREE = "Old tree deleted.";
const std::string ERROR_FILE_IS_NOT_OPEN = "File is not open!";
const std::string ERROR_HEAD_NOT_IN_TOP = "ERROR: Incorrect file - <<HEAD>> must be in top.";
const std::string ERROR_FORMAT = "ERROR: Incorrect file - format error.";

const std::string MENU_TEXT = R"("====================== Task 2.7 ======================="
"========================================================"
"= Enter each command finish pressing button <Enter>.   ="
"=                                                      ="
"= Commands:                                            ="
"= `a` - load tree from file                            ="
"= `s` - print tree                                     ="
"= `d` - calc                                           ="
"= `f` - delete tree                                    ="
"=                                                      ="
"= `q` - close                                          ="
"========================================================")";


struct Tree
{
    std::string name;
    int depth;
    Tree *father;   
    Tree *brother;  
    Tree *child;    
};

struct ListDepartment
{
    std::string name;
    ListDepartment *next;
};

struct TecherCalc
{
    std::string name;
    ListDepartment *departments;
    TecherCalc *next;
};

Tree* createTreeElement(std::string name, int depth, Tree *father, Tree *brother, Tree *child)
{
    Tree *curr = new Tree;
    curr->name = name;
    curr->depth = depth;
    curr->father = father;
    curr->brother = brother;
    curr->child = child;    
    return curr;    
}

void printTree(Tree *head, std::string spaces)
{
    if (head != 0)
    {
        std::cout << spaces << head->name << std::endl;
        printTree(head->child, spaces + SPACES);
        printTree(head->brother, spaces);
    }
}

void deleteTree(Tree *head, std::string spaces)
{
    if (head != 0)
    {
        deleteTree(head->child, spaces + SPACES);
        deleteTree(head->brother, spaces);
        std::cout << "DELETE " << spaces << head->name << std::endl;
        delete(head);
    }
}

void createTree(std::ifstream &finput, Tree *&head, int lvl) 
{
    std::string inputFile;
    std::smatch resultSearch;
    const std::regex searchChild(FORMAT_SEARCH_CHILDS);
    const std::regex searchHead(FORMAT_SEARCH_HEAD);

    int level = lvl;
    while (getline(finput, inputFile))
    {
        if (level == -1)
        {
            if (std::regex_match(inputFile, resultSearch, searchHead))
            {
                level++;
                Tree *curr = createTreeElement(resultSearch[1], level, 0, 0, 0);
                head = curr;
                createTree(finput, head, level);
                return;
            }
            else
            {
                std::cout << ERROR_HEAD_NOT_IN_TOP << std::endl;
                return;
            }
        }
        else
        {
            if (std::regex_match(inputFile, resultSearch, searchChild))
            {
                if (level == resultSearch[1].length())  //brother
                {   
                    Tree *curr = createTreeElement(resultSearch[2], level, head->father, 0, 0);
                    head->brother = curr;
                    createTree(finput, curr, level);
                    return;
                }
                else if (level - resultSearch[1].length() == -1) //son
                {
                    level = resultSearch[1].length();
                    Tree *curr = createTreeElement(resultSearch[2], level, head, 0, 0);
                    head->child = curr;
                    createTree(finput, curr, level);
                    return;
                }
                else if (level - resultSearch[1].length() == 1) //uncle
                {
                    level = resultSearch[1].length();
                    Tree *curr = createTreeElement(resultSearch[2], level, head->father->father, 0, 0);
                    head->father->brother = curr;
                    createTree(finput, curr, level);
                    return;
                }
                else if (level - resultSearch[1].length() == 2) //grandfather's brother
                {
                    level = resultSearch[1].length();                  
                    Tree *curr = createTreeElement(resultSearch[2], level, head->father->father->father, 0, 0);
                    head->father->father->brother = curr;
                    createTree(finput, curr, level);
                    return;
                }
            }
            else
            {
                std::cout << ERROR_FORMAT << std::endl;
                return;
            }
        }
    }
    std::cout << TREE_LOADED << std::endl;
}

void loadTreeFromFile(Tree *&head)
{
    std::ifstream fin;
    fin.open(FILE_PATH);
    if (!fin)
    {
       std::cout << ERROR_FILE_IS_NOT_OPEN << std::endl;
       return;
    }
    if (head != 0)
    {
        std::cout << DELETE_OLD_TREE << std::endl;
        deleteTree(head, "");
        head = 0;
        std::cout << DELETED_OLD_TREE << std::endl;
    }
    createTree(fin, head, -1);
    fin.close();  
}

TecherCalc* findElementByName(std::string name, TecherCalc *s)
{
    while (s != 0)
    {
        if (s->name == name)
        {
            return s;
        }
        else
        {
            s = s->next;
        }
        
    }
    return 0;    
}

ListDepartment* findDepByName(std::string name, ListDepartment *d)
{
    while (d != 0)
    {
        if (d->name == name)
        {
            return d;
        }
        else
        {
            d = d->next;
        }
        
    }
    return 0;    
};

void calculation(Tree *head, TecherCalc *&start)
{
    TecherCalc *curr;
    TecherCalc *newest;
    ListDepartment *dep;
    if (head != 0)
    {
        if (head->child == 0)
        {
            curr = findElementByName(head->name, start); 
            if (curr == 0)
            {
                newest = new TecherCalc;
                newest->name = head->name;
                newest->departments = new ListDepartment;
                    if (head->depth == DEPTH_TEACHER)
                        newest->departments->name = head->father->father->name;
                    else 
                        newest->departments->name = head->father->name;
                    newest->departments->next = 0;
                newest->next = start;
                start = newest;
            } 
            else
            {
                ListDepartment *ld = new ListDepartment;
                dep = findDepByName(head->father->father->name, curr->departments);
                if (dep == 0)
                {
                    if (head->depth == DEPTH_TEACHER)
                        ld->name = head->father->father->name;
                    else 
                        ld->name = head->father->name;
                    ld->next = curr->departments;
                    curr->departments = ld;
                } 
            }
        }
        calculation(head->child, start);
        calculation(head->brother, start);
    }
}

void printListDepartment(ListDepartment *start)
{
    while (start != 0)
    {
        std::cout << " [" << start->name << "]";
        start = start->next;
    }
}

int countListDepartment(ListDepartment *start)
{
    int count = 0;
    while (start != 0)
    {
        count++;
        start = start->next;
    }
    return count;
}

void calc(Tree *head)
{
    TecherCalc *start = 0;
    calculation(head, start);
    while (start != 0)
    {
        if (countListDepartment(start->departments) >= 3)
        {
            std::cout << start->name; 
            printListDepartment(start->departments);
            std::cout << std::endl;
        }
        start = start->next;
    }
}

void showMainMenu()
{
    system("cls");
    std::cout << MENU_TEXT << std::endl;
}

void mainMenu()
{
    char inputKey;
    Tree *HEAD = 0;

    showMainMenu();
    do
    {
        std::cout << "Enter command: ";
        std::cin >> inputKey;
        switch (inputKey) {
            case 'a':
                loadTreeFromFile(HEAD);
                break;
            case 's':
                printTree(HEAD, "");
                break;
            case 'd': 
                calc(HEAD);
                break;
            case 'f':
                deleteTree(HEAD, "");
                HEAD = 0;
                break;
        }
    } 
    while (inputKey != 'q');
    deleteTree(HEAD, "");
}

int main()
{
    mainMenu();
}