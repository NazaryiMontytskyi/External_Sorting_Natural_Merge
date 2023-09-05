//
// Created by nazar on 04.09.2023.
//

#include "files_functions.h"

void initialize_file(const string &filename) {
    vector<int> vec = {42, 17, 88, 53, 29, 64, 5, 91, 12, 77, 3, 55, 44, 68, 37, 19, 62, 8, 96, 24, 70, 11, 41, 76, 6, 33, 50, 99, 22};
    ofstream out_file;
    out_file.open(filename, ios::binary);

    for(int i = 0; i < vec.size(); i++)
        out_file.write((char*)&vec[i], sizeof(int));
    out_file.close();

}

void show_file(const string &filename) {
    ifstream in_file;

    in_file.open(filename, ios::binary);
    int var;
    while(in_file.read((char*)&var, sizeof(int)))
        cout << var << " ";
    cout << endl;
    in_file.close();
}