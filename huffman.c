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
void buildHoffmanTree(Node * * tree, List * listFq);
unsigned int * letterFrequency (FILE * file, List * list);
void letterFrequencyToList(unsigned int * list, List * l);
Node * removeMinTree(List * l);
List * transformNodeTree(List * listFreq);
bool generateCode (Node * tree, Byte b, char * buffer, int size);
void frequencyArrayToListFreq (unsigned int * array, List * list);
int generateBit (FILE * file, unsigned position, Byte * aux);


//Public
void compress(char fileIn[], char fileOut[]) {
	FILE * fileInF = fopen(fileIn, "rb");
	FILE * fileOutF = fopen(fileOut, "wb");

	if(fileInF == NULL) {
		printf("Error: Arquivo não existe");
		return;
	}

	//Pegar frequencias
	List * listFrequency = list();
	unsigned int * toFile = letterFrequency(fileInF, listFrequency);

	//Montar Arvore
	Node * tree;

	buildHoffmanTree(&tree,listFrequency);

	Byte b;

	void * * arrList = getAllList(listFrequency);
	int i;


	for (i = 0; i < length(listFrequency); i++) {
		Frequency f = getFrequency(arrList[i]);
		char buffer[1024] = {0};
		generateCode(tree,f.letter, buffer,0);
		printf("Letter: %c | Code: %d \n",(char)f.letter, f.frequency);
	}

	printf("\n\n\nExistem %d diferentes\n\n\n", length(listFrequency));


	fseek(fileOutF, sizeof(unsigned int), SEEK_CUR);
	fwrite(toFile, 256, sizeof(toFile[0]), fileOutF);

	//Compress File
	Byte c;
	unsigned int size = 0;
	Byte aux;

	while(fread(&c,1,1,fileInF) >= 1) {

		char buffer[1024] = {0};
		generateCode(tree,c, buffer,0);
        char * i;
		// Basicamente, converte o buffer binario em inteiro.
		for (i = buffer; *i; i++){

			if(*i == '1') {
				aux = aux | (1 << (size % 8));
			}
			size++;

			//Se formou 1 byte, Escreve no arquivo
			if(size % 8 == 0) {
				fwrite(&aux, 1,1,fileOutF);
				aux = 0;
			}

			//printf("%c",*i);
		}

	}

	fwrite(&aux, 1, 1, fileOutF);

	fseek(fileOutF,0,SEEK_SET);

	fwrite(&size,1,sizeof(unsigned),fileOutF);

	free(toFile);
	fclose(fileOutF);
	fclose(fileInF);

	printf("\n\n");

	printInOrdem(tree);
}

//Public
void decompress(char fileIn[], char fileOut[]) {
	FILE * fileInF = fopen(fileIn, "rb");
	FILE * fileOutF = fopen(fileOut, "wb");

	if(fileInF == NULL) {
		printf("Error: Arquivo não existe");
		return;
	}

	unsigned listBytes [256] = {0};
	unsigned int size;

	fread(&size,1,sizeof(size), fileInF);
	fread(listBytes,256,sizeof(listBytes[0]),fileInF);

	List * listFrequency = list();

	frequencyArrayToListFreq(listBytes,listFrequency);

	Node * treeHoffman;
	buildHoffmanTree(&treeHoffman,listFrequency);

	
	
	

	unsigned position = 0;

	Byte aux = 0;

	while (position < size) {
		Node * nodeActual = treeHoffman;

		while (!isLeaf(nodeActual)) {
			int result = generateBit(fileInF,position++,&aux);
			nodeActual =  result ? getLeft(nodeActual) : getRight(nodeActual);
		}
		Byte write = getHuffmanNode(getBin(nodeActual)).byte;
		
		fwrite(&write, 1, 1, fileOutF);
	}

}

//Private
int generateBit (FILE * file, unsigned position, Byte * aux) {
	if (position % 8 == 0) {
		fread(aux, 1, 1, file);
	}
	return !!((*aux) & (1 << (position % 8)));
}

//Private
bool generateCode (Node * tree, Byte b, char * buffer, int size) {
	HuffmanNode * node = (HuffmanNode *)getBin(tree);

	if (isLeaf(tree) && node->byte == b) {
		buffer[size] = '\0';
		return true;
	} else {
		bool finded = false;

		if(getLeft(tree) != NULL) {
			buffer[size] = '0';
			finded = generateCode(getLeft(tree), b, buffer, size+1);
		}

		if(getRight(tree) != NULL && !finded) {
			buffer[size] = '1';
			finded = generateCode(getRight(tree), b, buffer, size+1);
		}

		if(!finded) {
			buffer[size] = '\0';
		}

		return finded;
	}
}

//Private
unsigned int * letterFrequency (FILE * file, List * list) {
	//TODO: Lembrar de dar free;
	Byte byte;
	unsigned int * listByteTemp = (unsigned int *) malloc(256*sizeof(unsigned int));
	int i;
	for (i = 0; i < 256; i++) {
		listByteTemp[i] = 0;
	}

	while (fread(&byte, 1, 1, file) >= 1) {
		listByteTemp[byte]++;
	}

	letterFrequencyToList(listByteTemp, list);
	rewind(file);
	return listByteTemp;
}

void letterFrequencyToList(unsigned int * list, List * l) {
	int i;
	for (i = 0; i < 256; i++) {
		if(list[i] > 0) {
			Frequency * fq = (Frequency *) malloc(sizeof(Frequency));
			fq->frequency = list[i];
			fq->letter = i;
			listAdd(l,fq);
		}
	}
}

//Private
void frequencyArrayToListFreq (unsigned int * array, List * list) {
	int i;
	for (i = 0; i < 256; i++) {
		if(array[i] > 0) {
		Frequency * feq = (Frequency *) malloc(sizeof(Frequency));
		feq->frequency = array[i];
		feq->letter = i;
		listAdd(list, feq);
		}
	}
}

//Private
void buildHoffmanTree(Node * * tree, List * listFq) {
	List * listHuff = transformNodeTree(listFq);

	while (length(listHuff) > 1) {
		Node * nodeDir = removeMinTree(listHuff);
		
		Node * nodeEsq = removeMinTree(listHuff);

		

		HuffmanNode * sum = (HuffmanNode *) malloc(sizeof(HuffmanNode));
		sum->byte = '#';
		sum->frequency = getHuffmanNode(getBin(nodeEsq)).frequency + getHuffmanNode(getBin(nodeDir)).frequency;

		Node * nodeSum = newNode('#',sum, nodeEsq, nodeDir);

		listAdd(listHuff,nodeSum);

	}

	*tree = (Node *) getValue(listHuff, 0);
	destroyList(listHuff);
}

//Private
List * transformNodeTree(List * listFreq) {
	List * t = list();
	int i;

	void * * listInArray = getAllList(listFreq);
	for (i = 0; i < length(listFreq); i++) {
		HuffmanNode * temp = (HuffmanNode *) malloc(sizeof(HuffmanNode));
		temp->byte = getFrequency(listInArray[i]).letter;
		temp->frequency = getFrequency(listInArray[i]).frequency;

		listAdd(t,newNode((int) getFrequency(listInArray[i]).letter, temp, NULL ,NULL));
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
		HuffmanNode fq = getHuffmanNode(getBin(listInArray[i]));
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
