/* условия задачи:
    Задача 1.18.
    Организовать в основной памяти с помощью указателей
    стек из очередей. Обеспечить операции ведения очереди из
    вершины стека, расширения и сокращения стека, выдачи
    содержимого стека (9).
*/

// Среда разработки: VS Code. C/C++
// Compiler: mingw64 g++

#include <iostream>
#include <string>

const std::string STACK_EMPTY = "Stack empty.";
const std::string STACK_DELETED = "Stack deleted.";
const std::string STACK_ELEMENT_ADDED = "Added new element of stack.";
const std::string STACK_ELEMENT_DELETED = "Element of stack deleted.";
const std::string STACK_ELEMENT_FIRST_OUT = "FIRST OUT -> ";
const std::string STACK_ELEMENT_FIRST_IN = "<- FIRST IN";

const std::string QUEUE_EMPTY = "Queue empty.";
const std::string QUEUE_DELETED = "Queue deleted.";
const std::string QUEUE_ELEMENT_ADDED = "Added new element of queue.";
const std::string QUEUE_ELEMENT_DELETED = "Element of queue deleted.";
const std::string INPUT_QUEUE_ELEMENT_DATA = "Enter new element of queue (without spaces): ";
const std::string INPUT_QUEUE_ELEMENTS_DATA = "Enter new elements of queue through space: ";


const std::string INCORRECT_INPUT_QUEUE_ELEMENTS = "You enter no one element of queue.";
const std::string INCORRECT_INPUT = "Incorrect enter.";
const std::string MENU_TEXT = R"("====================== Task 1.18 ======================="
"========================================================"
"= Enter each command finish pressing button <Enter>.   ="
"=                                                      ="
"= Commands:                                            ="
"= stack                                                ="
"= `s` - print                                          ="
"= `a` - add new element                                ="
"= `d` - delete element                                 ="
"= queue                                                ="
"= `x` - print                                          ="
"= `z` - add new element                                ="
"= `c` - delete element                                 ="
"=                                                      ="
"= `q` - close                                          ="
"========================================================")";

struct Queue
{
    std::string data;
    Queue *nextElem;
};

void printQueue(Queue *head) 
{
    if (head == 0) 
    {
        std::cout << QUEUE_EMPTY;
    }
    else
    {
        while (head != 0)
        {
            std::cout << head->data << " ";
            head = head->nextElem;
            if (head != 0) std::cout << "-> ";
        }
    }      
}

void addElementQueue(Queue *&head, Queue *&tail, std::string data) 
{
    Queue *newElem = new Queue;

    newElem->data = data;
    newElem->nextElem = 0;

    if (tail == 0)
    {
        tail = newElem;
        head = newElem;
    }
    else
    {
        tail->nextElem = newElem;
        tail = newElem;
    }
    std::cout << QUEUE_ELEMENT_ADDED;
}

void deleteElementQueue(Queue *&head)
{
    if (head == 0)
    {
        std::cout << QUEUE_EMPTY;
    }
    else
    {
        Queue *curr = head;
        head = head->nextElem;
        delete curr;
        std::cout << QUEUE_ELEMENT_DELETED;
    }
}

void deleteQueue(Queue *&head)
{
    if (head == 0)
    {
        std::cout << QUEUE_EMPTY;
    }
    else
    {
        while (head != 0)
        {
            deleteElementQueue(head);
            std::cout << std::endl;
        }
        std::cout << QUEUE_DELETED;
    }
}

bool createQueue(Queue *&head, Queue *&tail, std::string datas)
{
    std::string queueData;
    int posSpace, count = 0;

    posSpace = datas.find(" ");
    while (posSpace != -1)
    {
       if (posSpace != 0)
       {
            queueData = datas.substr(0, posSpace);
            addElementQueue(head, tail, queueData);
            std::cout << std::endl;
            count++;
            datas = datas.substr(posSpace, datas.length() - queueData.length());
       }
       else
       {
           datas = datas.substr(1, datas.length() - 1);
       }
       posSpace = datas.find(" ");
    }
    if (datas.length() != 0) 
    {
        addElementQueue(head, tail, datas);
        std::cout << std::endl;
        count++;
    }
    if (count == 0) 
    {
        std::cout << INCORRECT_INPUT_QUEUE_ELEMENTS << std::endl;
    }
    return count != 0;
}

struct Stack
{
    Queue *head;
    Queue *tail;
    Stack *prevElem;
};

void printStack(Stack *l) 
{
    int i = 0;
    
    if (l == 0) {
        std::cout << STACK_EMPTY << std::endl; 
    }
    else
    {
        while (l != 0)
        {
            i++;
            if (i == 1) 
            {
                std::cout << STACK_ELEMENT_FIRST_OUT;
            }
            else
            {
                std::cout << "             ";
            }
            printQueue(l->head);
            l = l->prevElem;
            if (l == 0) 
            {
                std::cout << STACK_ELEMENT_FIRST_IN;
            }
            std::cout << std::endl;
        }
    }
}

void addElementStack(Stack *&l, std::string queueDatas)
{
    Queue *first = 0;
    Queue *last = 0;
    
    if (createQueue(first, last, queueDatas))
    {
        Stack *curr = new Stack;   
        curr->prevElem = l;
        curr->head = first;
        curr->tail = last;
        l = curr;
        std::cout << STACK_ELEMENT_ADDED;
    }
}

void deleteElementStack(Stack *&l)
{
    if (l == 0)
    {
        std::cout << STACK_EMPTY;
    }
    else
    {
        Stack *curr = l;
        l = l->prevElem;
        deleteQueue(curr->head);
        std::cout << std::endl;
        delete curr;
        std::cout << STACK_ELEMENT_DELETED;
    } 
}

void deleteStack(Stack *&l)
{
    if (l == 0)
    {
        std::cout << STACK_EMPTY;
    }
    else
    {
        while (l != 0) 
        {
            deleteElementStack(l);
            std::cout << std::endl;
        }
        std::cout << STACK_DELETED;
    }
}

void commandAddElementStack(Stack *&l)
{
    std::string inputQueueDatas;

    std::cin.ignore(32767, '\n'); 
    std::cout << INPUT_QUEUE_ELEMENTS_DATA;
    std::getline(std::cin, inputQueueDatas);
    addElementStack(l, inputQueueDatas);
    std::cout << std::endl;
}

Queue* getFirstQueueElement(Stack *l)
{
    if (l == 0) 
    {
        return 0; 
    }
    else
    {
        return l->head;
    }
}

Queue* getLastQueueElement(Stack *l)
{
    if (l == 0) 
    {
        return 0; 
    }
    else
    {
        return l->tail;
    }
}

void commandAddElementQueue(Stack *l)
{
    Queue *first = 0;
    Queue *last = 0;

    if (l == 0)
    {
        std::cout << STACK_EMPTY << std::endl;
    }
    else
    {
        std::string inputData;

        std::cin.ignore(32767, '\n'); 
        std::cout << INPUT_QUEUE_ELEMENT_DATA;
        std::getline(std::cin, inputData);
        if ((inputData.find(" ") == -1) && (inputData.length() != 0))
        {
            first = getFirstQueueElement(l);
            last = getLastQueueElement(l);
            addElementQueue(first, last, inputData);
            l->tail = last;
            std::cout << std::endl;
        }
        else
        {
            std::cout << INCORRECT_INPUT << std::endl;
        }
    }
}

void commandDeleteElementQueue(Stack *&l)
{
    Queue *first = 0;
    
    if (l == 0)
    {
        std::cout << STACK_EMPTY << std::endl;
    }
    else
    {
        first = getFirstQueueElement(l);
        if (first->nextElem != 0)
        {
            deleteElementQueue(first);
            l->head = first;
        }
        else
        {
            deleteElementStack(l);
        }
        std::cout << std::endl;
    }
}

void commandPrintQueue(Stack *l)
{
    Queue *first = 0;
    
    if (l == 0)
    {
        std::cout << STACK_EMPTY << std::endl;
    }
    else
    {
        first = getFirstQueueElement(l);
        printQueue(first);
        std::cout << std::endl;
    }
}

void commandDeleteElementStack(Stack *&l)
{
    deleteElementStack(l);
    std::cout << std::endl;
}

void commandPrintStack(Stack *l)
{
    printStack(l);
}

void showMainMenu()
{
    system("cls");
    std::cout << MENU_TEXT << std::endl;
}

void mainMenu()
{
    char inputKey;
    Stack *lastStackElement = 0;

    showMainMenu();
    do
    {
        std::cout << "Enter command: ";
        std::cin >> inputKey;
        switch (inputKey) {
            case 's':
                commandPrintStack(lastStackElement); 
                break;
            case 'a':
                commandAddElementStack(lastStackElement); 
                break;
            case 'd': 
                commandDeleteElementStack(lastStackElement);
                break;
            case 'x':
                commandPrintQueue(lastStackElement);
                break;
            case 'z':
                commandAddElementQueue(lastStackElement);
                break;
            case 'c':
                commandDeleteElementQueue(lastStackElement);
                break;
        }
    } 
    while (inputKey != 'q');
    deleteStack(lastStackElement);
}

int main() 
{
    mainMenu();
}