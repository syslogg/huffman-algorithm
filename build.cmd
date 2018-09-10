SET PATH=%PATH%;%1
gcc -g main.c generics/List.h generics/Tree.h generics/list/LinkedList.c generics/tree/TreeBin.c huffman/huffman.c huffman/huffman.h -o %2