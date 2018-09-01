#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Tree.h"
#include "List.h"

#define bool int
#define false 0
#define true 1

#define TEST printf("\nLetter: %c | Fq: %d", (char)fq.letter, fq.frequency);

typedef unsigned char Byte;
typedef struct frequency Frequency;
typedef struct huffmanNode HuffmanNode;

struct frequency {
	int frequency;
	Byte letter;
};

 struct huffmanNode {
	 int frequency;
	Byte byte;
 };

//Declaring
Frequency getFrequency (void * freq);
HuffmanNode getHuffmanNode (void * huff);
void buildHoffmanTree(Node * tree, List * listFq);
void letterFrequency (FILE * file, List * list);
Node * removeMinTree(List * l);
List * transformNodeTree(List * listFreq);


//Public
void compress(char file[]) {
	FILE * fileIn = fopen(file, "rb");
	//FILE * fileOut = fopen(file, "wb");
	
	if(fileIn == NULL) {
		printf("Error: Arquivo não existe");
		return;
	}
	
	//Pegar frequencias
	List * listFrequency = list();
	letterFrequency(fileIn, listFrequency);

	//Montar Arvore
	Node * tree;

	buildHoffmanTree(tree,listFrequency);
	
}

//Public
void decompress(char file[]) {
	FILE * fileIn = fopen(file, "rb");
	//FILE * fileOut = fopen(file, "w");
	
	if(fileIn == NULL) {
		printf("Error: Arquivo não existe");
		return;
	}
}

//Private
void letterFrequency (FILE * file, List * list) {
	
	Byte byte;
	unsigned listByteTemp[256] = {0};
	
	while (fread(&byte, 1, 1, file) >= 1) {
		listByteTemp[byte]++;
	}

	int i;
	for (i = 0; i < 256; i++) {
		if(listByteTemp[i] > 0) {
			Frequency * fq = (Frequency *) malloc(sizeof(Frequency));
			fq->frequency = listByteTemp[i];
			fq->letter = i;
			listAdd(list,fq);
		}
	}
	
	rewind(file);
}

//Private
void buildHoffmanTree(Node * tree, List * listFq) {
	List * listHuff = transformNodeTree(listFq);

	while (length(listHuff) > 1) {
		Node * nodeEsq = removeMinTree(listHuff);

		Node * nodeDir = removeMinTree(listHuff);

		HuffmanNode * sum = (HuffmanNode *) malloc(sizeof(HuffmanNode)); 
		sum->byte = '#';
		sum->frequency = getHuffmanNode(getBin(nodeEsq)).frequency + getHuffmanNode(getBin(nodeDir)).frequency;

		Node * nodeSum = newNode('#',sum, nodeEsq, nodeDir);

		listAdd(listHuff,nodeSum);

	}
	Node * root = (Node *) getValue(listHuff, 0);
	//printf("LISTA: %d", length(listHuff));
	printInOrdem(root);
}

//Private
List * transformNodeTree(List * listFreq) {
	List * t = list();
	int i;

	void * * listInArray = getAllList(listFreq);
	for (i = 0; i < length(listFreq); i++) {
		HuffmanNode * temp = (HuffmanNode *) malloc(sizeof(HuffmanNode));
		temp->byte = getFrequency(listInArray[i]).letter;
		temp->byte = getFrequency(listInArray[i]).letter;

		listAdd(t,newNode((int)getFrequency(listInArray[i]).letter,temp,NULL,NULL));
	}
	return t;
}

//Private
Frequency getFrequency (void * freq) {
	return * (Frequency *) freq;
}

//Private
HuffmanNode getHuffmanNode (void * huff) {
	return * (HuffmanNode *) huff;
}

//Private
Node * removeMinTree(List * l) {
	int i, minFeq = INT_MAX, minIndex = -1;
	void * * listInArray = getAllList(l);
	for (i = 0; i < length(l); i++) {
		HuffmanNode fq = getHuffmanNode(listInArray[i]);
		if(minFeq > fq.frequency) {
			minFeq = fq.frequency;
			minIndex = i;
		}
	}
	if(minIndex == -1) {
		printf("ERROR: Nao há minFeq");
		return NULL;
	}

	Node * nodeReturned = listInArray[minIndex];
	listRemove(l, minIndex);

	return nodeReturned;
}