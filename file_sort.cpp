//
// Created by nazar on 04.09.2023.
//

#include "file_sort.h"

fileSorter::fileSorter(string nameOfFile): nameOfFile(nameOfFile) {
    A_SIZE = std::filesystem::file_size(nameOfFile)/sizeof(int);
}

void fileSorter::divideFile() {
    A_in.open(nameOfFile, ios::binary);
    B_out.open(B_FILE, ios::binary);
    C_out.open(C_FILE, ios::binary);

    series_counter = 0;
    var_counter = 0;

    if (A_SIZE <= 1) {
        A_in.close();
        B_out.close();
        C_out.close();

        return;
    }

    A_in.read((char *) &prev, sizeof(int));
    B_out.write((char *) &prev, sizeof(int));
    A_in.read((char *) &curr, sizeof(int));
    var_counter += 2;

    while (var_counter <= A_SIZE)
    {
        if (prev > curr)
        {
            series_counter++;
        }

        prev = curr;
        var_counter++;
        A_in.read((char*)&curr,sizeof(int));

        if(!(series_counter % 2))
        {
            B_out.write((char*)&prev, sizeof(int));
            continue;
        }

        C_out.write((char*)&prev, sizeof(int));
    }
    series_counter++;

    A_in.close();
    B_out.close();
    C_out.close();
}

fileSorter::~fileSorter() {

}

int fileSorter::series_last_pos(int first_pos, const string& filename) {

    ifstream first_stream;
    ifstream second_stream;

    first_stream.open(filename, ios::binary);
    second_stream.open(filename, ios::binary);

    int p_curr, p_next;
    int i;

    first_stream.read((char*)&p_curr, sizeof(int));
    for(int j = 0; j < 2; j++)
        second_stream.read((char*)&p_next, sizeof(int));

    if(p_curr > p_next)
        return first_pos + 1;

    for(i = 1; i < first_pos; i++)
    {
        first_stream.read((char*)&p_curr, sizeof(int));
        second_stream.read((char*)&p_next, sizeof(int));
    }

    while(p_curr < p_next)
    {
        first_stream.read((char*)&p_curr, sizeof(int));
        second_stream.read((char*)&p_next, sizeof(int));
        i++;
    }

    first_stream.close();
    second_stream.close();

    return i;
}

void fileSorter::merge() {

    A_out.open(nameOfFile, ios::binary);
    B_in.open(B_FILE, ios::binary);
    C_in.open(C_FILE, ios::binary);

    B_series_counter = 0;
    C_series_counter = 0;

    int B_var_counter = 0;
    int C_var_counter = 0;

    int B_SIZE = std::filesystem::file_size(B_FILE)/sizeof(int);
    int C_SIZE = std::filesystem::file_size(C_FILE)/sizeof(int);

    int B_prev, B_curr;
    int C_prev, C_curr;

    B_in.read((char*)&B_curr, sizeof(int));
    B_prev = B_curr;
    C_in.read((char*)&C_curr, sizeof(int));
    C_prev = C_curr;

    if (B_curr < C_curr)
    {
        A_out.write((char*)&B_curr, sizeof(int));
        B_in.read((char*)&B_curr,sizeof(int));
        B_var_counter++;
    }
    else{
        A_out.write((char*)&C_curr,sizeof(int));
        C_in.read((char*)&C_curr,sizeof(int));
        C_var_counter++;
    }

    while(B_var_counter < B_SIZE and C_var_counter < C_SIZE)
    {
        if(B_prev > B_curr)
        {
            B_series_counter++;
        }
        if(C_prev > C_curr)
        {
            C_series_counter++;
        }

        if(B_series_counter == C_series_counter)
        {
            if(B_curr > C_curr)
            {
                A_out.write((char*)&C_curr, sizeof(int));
                C_prev = C_curr;
                C_in.read((char*)&C_curr, sizeof(int));
                C_var_counter++;
            }
            else{
                A_out.write((char*)&B_curr, sizeof(int));
                B_prev = B_curr;
                B_in.read((char*)&B_curr, sizeof(int));
                B_var_counter++;
            }
        }

        while(B_series_counter < C_series_counter)
        {
            A_out.write((char*)&B_curr, sizeof(int));
            B_prev = B_curr;
            B_in.read((char*)&B_curr,sizeof(int));
            B_var_counter++;

            if(B_prev > B_curr || B_var_counter == B_SIZE)
            {
                B_series_counter++;
            }
        }

        while(B_series_counter > C_series_counter)
        {
            A_out.write((char*)&C_curr, sizeof(int));
            C_prev = C_curr;
            C_in.read((char*)&C_curr,sizeof(int));
            C_var_counter++;

            if(C_prev > C_curr || C_var_counter == C_SIZE)
            {
                C_series_counter++;
            }
        }


    }

    while(B_var_counter < B_SIZE)
    {
        A_out.write((char*)&B_curr, sizeof(int));
        B_in.read((char*)&B_curr, sizeof(int));
        B_var_counter++;
    }
    while(C_var_counter < C_SIZE)
    {
        A_out.write((char*)&C_curr, sizeof(int));
        C_in.read((char*)&C_curr, sizeof(int));
        C_var_counter++;
    }

    A_out.close();
    B_in.close();
    C_in.close();

}

void fileSorter::sort() {
    while((series_counter != 2)){
        this->divideFile();
        this->merge();
    }
}
