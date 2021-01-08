/* условия задачи:
    Задача 4.3. 
    В текстовом файле задана последовательность целых чисел.
    Отсортировать файл методом простого слияния с 3 лентами (8).
*/

// Среда разработки: VS Code. C/C++
// Compiler: mingw64 g++

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <cmath>
#include <stdio.h>

#include "constants.h"

bool checkFile(std::fstream &fF)
{
    int currCh = -1, prevCh = -1;
    while((currCh = fF.get()) != EOF)
    {
        if (((char(prevCh) == ' ') || (char(prevCh) == '\n')) && ((char(currCh) == ' ') || (char(currCh) == '\n')))
            return false;
        if ((char(prevCh) == '-') && ((char(currCh) == ' ') || (char(currCh) == '-')))
            return false;
        if ((prevCh >= 48) && (prevCh <= 57) && (char(currCh) == '-'))
            return false;
        if (((currCh >= 48) && (currCh <= 57)) || (char(currCh) == '-') || (char(currCh) == ' ') || (char(currCh) == '\n'))
        {
            prevCh = currCh;
        }
        else
            return false;
    }
    if ((char(prevCh) == '\n') || (char(prevCh) == ' ') || (char(prevCh) == '-') || (prevCh == -1))
        return false;
    fF.close();
    return true;
}

bool getNumber(std::fstream &fF, int &number)
{
    int ch = -1, zn = 1, num = 0;
    bool hasNum = false;
    while(((ch = fF.get()) != EOF) && (char(ch) != ' '))
    {
        if (char(ch) == '-')
            zn = -1;
        if ((ch >= 48) && (ch <= 57))
            num = (num * 10) + (ch - 48);
        hasNum = true;
    }
    if (!hasNum)
        return false;
    number = num * zn;
    return true;
}

int fileCopy(std::fstream &fF, std::fstream &fT)
{
    int elem, countElem = 0;
    while (getNumber(fF, elem))
    {
        fT << elem;
        if (!fF.eof())
            fT << " ";
        countElem++;
    }
    return countElem;
}

void fileDivide(std::fstream &fFrom, std::fstream &fTo1, std::fstream &fTo2, int turn)
{
    int elem;
    bool isSecondFile = false, hasRecSec = false, hasRecFir = false;
    int numElem = 0;

    while (getNumber(fFrom, elem))
    {
        if (isSecondFile)
        {   
            if (hasRecSec)
                fTo2 << " ";
            fTo2 << elem;
            hasRecSec = true;
        }
        else
        {
            if (hasRecFir)
                fTo1 << " "; 
            fTo1 << elem;
            hasRecFir = true;
        }
        numElem++;
        if (numElem % turn == 0)
        {
            isSecondFile = !isSecondFile;
            numElem = 0;
        }
    }

    fFrom.close();
    fTo1.close();
    fTo2.close();  
}

void insertNumber(std::fstream &fF, bool isNotStart, int number)
{
    if (isNotStart) 
        fF << " ";
    fF << number;
}

void filesMerge(std::fstream &fF1, std::fstream &fF2, std::fstream &fT, int turn)
{
    int a, b, numElem1 = 0, numElem2 = 0;
    bool first = true, second = true, hasRec = false;

    while ((!fF1.eof()) && (!fF2.eof()))
    {
        if (first) 
        {
            getNumber(fF1, a);
            numElem1++;
        }
        if (second) 
        {
            getNumber(fF2, b);
            numElem2++;
        }

        if (a < b)
        {
            insertNumber(fT, hasRec, a);
            first = true;
            second = false;
        }
        else
        {
            insertNumber(fT, hasRec, b);
            first = false;
            second = true;
        }
        hasRec = true;

        if ((turn == 1) && ((numElem1 == 1) || (numElem2 == 1)))
        {
            if (!first) insertNumber(fT, hasRec, a);
            if (!second) insertNumber(fT, hasRec, b);
            first = true;
            second = true;
            numElem1 = 0;
            numElem2 = 0;
        }
        else if ((turn != 1) && ((numElem1 % turn == 0) || (numElem2 % turn == 0)))
        {
            bool *ttt; 
            int aaa;
            if (!first) {ttt = &first; aaa = a;}
            if (!second) {ttt = &second; aaa = b;}

            if (numElem2 % turn != 0)
            {
                while (numElem2 % turn != 0)
                {
                    if (!getNumber(fF2, b))
                        break;

                    if ((!*ttt) && (aaa < b))
                    {   
                        insertNumber(fT, hasRec, aaa);
                        *ttt = true;
                    }
                    insertNumber(fT, hasRec, b);
                    numElem2++;
                }
                if (!*ttt) 
                    insertNumber(fT, hasRec, aaa); 
                *ttt = true;
            }
            numElem2 = 0;

            if (numElem1 % turn != 0)
            {
                while (numElem1 % turn != 0)
                {
                    if (!getNumber(fF1, a))
                        break;

                    if ((!*ttt) && (aaa < a))
                    {   
                        insertNumber(fT, hasRec, aaa);
                        *ttt = true;
                    }
                    insertNumber(fT, hasRec, a);
                    numElem1++;
                }
                if (!*ttt) 
                    insertNumber(fT, hasRec, aaa); 
                *ttt = true;
            }
            numElem1 = 0;
        }            
    }
    
    bool flag; 
    int aaa;
    flag = first && second;
    if (!first) aaa = a;
    if (!second) aaa = b;

    if (!fF1.eof())
    {
        while (getNumber(fF1, a))
        {
            if ((!flag) && (aaa < a))
            {   
                insertNumber(fT, hasRec, aaa);
                flag = true;
            }
            insertNumber(fT, hasRec, a);
        }
        if (!flag) 
            insertNumber(fT, hasRec, aaa); 
        flag = true;
    }

    if (!fF2.eof())
    {
         while (getNumber(fF2, b))
         {
            if ((!flag) && (aaa < b))
            {   
                insertNumber(fT, hasRec, aaa);
                flag = true;
            }
            insertNumber(fT, hasRec, b);
        }
        if (!flag) 
            insertNumber(fT, hasRec, aaa); 
        flag = true;
    }

    fT.close();
    fF1.close();
    fF2.close();      
}

void calc()
{
    std::fstream fInp, fTemp1, fTemp2, fOut;
    int power = 0, turn, countElem;

    fInp.open(INPUT_FILE_PATH, std::ios::in);
    if (!checkFile(fInp))
    {
        fInp.close();
        std::cout << "Invalid format file!" << std::endl;
        return;
    }
        
    fInp.open(INPUT_FILE_PATH, std::ios::in);
    fOut.open(OUTPUT_PATH, std::ios::trunc | std::ios::out);
    countElem = fileCopy(fInp, fOut);
    fOut.close();
    fInp.close();

    while (countElem > (turn = pow(2, power)))
    {
        fOut.open(OUTPUT_PATH, std::ios::in);
        fTemp1.open(TEMP_FILE_1_PATH, std::ios::trunc | std::ios::out);
        fTemp2.open(TEMP_FILE_2_PATH, std::ios::trunc | std::ios::out);
        fileDivide(fOut, fTemp1, fTemp2, turn);
        
        fOut.open(OUTPUT_PATH, std::ios::trunc | std::ios::out);
        fTemp1.open(TEMP_FILE_1_PATH, std::ios::in);
        fTemp2.open(TEMP_FILE_2_PATH, std::ios::in);
        filesMerge(fTemp1, fTemp2, fOut, turn);

        power++;
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

    showMainMenu();
    do
    {
        std::cout << "Enter command: ";
        std::cin >> inputKey;
        switch (inputKey) {
            case 'a':
                calc();
                break;
            case 's':
                break;
        }
    } 
    while (inputKey != 'q');
}

int main()
{
    mainMenu();    
}