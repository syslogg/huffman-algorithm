#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"
#include "List.h"
#include "huffman.h"

int main (){

    compress("file.txt", "fileCompress.txt");
    decompress("fileCompress.txt", "fileDescompress.txt");
    //system("read -n 1 -s -p \"Press any key to continue...\"");
    //system("pause");
    getchar();

    return 0;
}
