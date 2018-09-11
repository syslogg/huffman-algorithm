#include <stdio.h>
#include <stdlib.h>

#include "generics/Tree.h"
#include "generics/List.h"
#include "huffman/huffman.h"

int main (){
    //system("rm fileCompress.txt");
    //system("rm fileDescompress.txt");

    compress("tests/file.txt", "fileCompress.ed2");
    decompress("fileCompress.ed2", "fileDescompress.txt");

    //system("read -n 1 -s -p \"Press any key to continue...\"");
    system("pause");
    //getchar();

    return 0;
}
