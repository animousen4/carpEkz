// CarpEkz_06_01_23.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "TSpisok.h"
using namespace std;
int main()
{   
    setlocale(LC_ALL, "rus");

    ifstream inputFile("Spisok.txt");
    ofstream outputFile("OutSpisok.txt");
    
    TCorr tspisok;

    inputFile >> tspisok;
    inputFile.close();

    tspisok.defaultSortBySum();
    outputFile << tspisok;
    outputFile.close();


}
