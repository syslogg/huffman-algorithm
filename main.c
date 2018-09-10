#include <stdio.h>
#include <stdlib.h>

#include "generics/Tree.h"
#include "generics/List.h"
#include "huffman/huffman.h"

int main (){
    //system("rm fileCompress.txt");
    //system("rm fileDescompress.txt");

    compress("tests/img.jpg", "img.ed2");
    decompress("img.ed2", "imgDescompress.jpg");

    //system("read -n 1 -s -p \"Press any key to continue...\"");
    system("pause");
    //getchar();

    return 0;
}
