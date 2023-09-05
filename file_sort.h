#ifndef EXTERNALSORTNATURALMERGE_FILE_SORT_H
#define EXTERNALSORTNATURALMERGE_FILE_SORT_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>
using namespace std;

const string B_FILE = "B.bin";
const string C_FILE = "C.bin";

class fileSorter{
private:
    string nameOfFile;
    int A_SIZE;

    ifstream A_in;
    ifstream B_in;
    ifstream C_in;

    ofstream A_out;
    ofstream B_out;
    ofstream C_out;

    int series_counter;
    int var_counter;
    int prev, curr;

    int B_series_counter = 0;
    int C_series_counter = 0;
public:
    fileSorter(string nameOfFile);
    ~fileSorter();
    void divideFile();
    void merge();
    void sort();
public:
    int series_last_pos(int first_pos, const string& filename);
};

#endif //EXTERNALSORTNATURALMERGE_FILE_SORT_H
