#include "file_sort.h"
#include "files_functions.h"

int main() {
    string filename = "A.bin";
    initialize_file(filename);
    show_file(filename);
    fileSorter test(filename);

    test.sort();

    show_file(filename);



    return 0;
}
