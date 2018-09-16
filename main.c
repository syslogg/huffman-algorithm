#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "generics/Tree.h"
#include "generics/List.h"
#include "huffman/huffman.h"

#define bool int
#define false 0
#define true 1

#define FORMAT ".ed2"

void console(bool write);
void command(char * cmd);
void clear();
char * chooseFile(char * directory, bool filter);
char * limiter();
bool is_file(const char* path);
bool is_dir(const char* path);
void orderByDirectory(List * listDir);

int main (){
    console(true);
    getchar();

    return 0;
}

void console(bool write) {
    while (write) {
        char input[500];
		printf(">");
		fflush(stdin);
		scanf("%s",input);
		fflush(stdin);
		command(input);
        printf("\n");
    }
}

void command(char * cmd) {
    
    char params[10][100];

    if(sscanf(cmd,"compress %s",params[0]) > 0) {
        clear();
        double size, sizeOut;
        char fileName[500];
        strcpy(fileName, params[0]);
        strcat(fileName, FORMAT);
        if(compress(params[0], fileName,&size, &sizeOut) == true) {         
            printf("Arquivo comprimido!\n");
            printf("Tamanho do Arquivo Original: %g Kb\n", size/1024);
            printf("Tamanho do Arquivo Comprimido: %g Kb\n",sizeOut/1024);
        }
    } else if(!strcmp(cmd,"compress")) {
        clear();
        char * file = chooseFile(".", false);
        char cmds[500] = "compress ";
        strcat(cmds,file);
        command(cmds);
        free(file);
    } else if (sscanf(cmd,"decompress %s",params[0]) > 0) {
        clear();
        char fileName[500], format[8] = FORMAT;
        strcpy(fileName, params[0]);
        fileName[strlen(params[0])-strlen(format)] = '\0';
        if(decompress(params[0], fileName) == true) {
            printf("Arquivo descompactado com sucesso!!!\n");
            printf("Arquivo: %s\n", fileName);
        }
        
    } else if(!strcmp(cmd,"decompress")) {
        clear();
        char * file = chooseFile(".", true);
        char cmds[500] = "decompress ";
        strcat(cmds,file);
        command(cmds);
        free(file);
    }

}

char * chooseFile(char * directory, bool filter) {
    clear();

    printf("Selecione o arquivo que você quer compactar.\n\n");

    DIR * dir;
    struct dirent *lsdir;

    dir = opendir(directory);

    List * directoriesActual = list();

    int i = 1;

    while (( lsdir = readdir(dir) ) != NULL) {
        if(!(!strcmp(lsdir->d_name, ".") || !strcmp(lsdir->d_name,".."))){

            if(filter == true) {
                char temp[100];
                strcpy(temp,directory);
                strcat(temp,limiter());
                strcat(temp,lsdir->d_name);

                if(is_file(temp)) {
                    if(strstr(lsdir->d_name, FORMAT) != NULL) {
                        push(directoriesActual,lsdir->d_name);
                    }
                } else {
                    push(directoriesActual,lsdir->d_name);
                }
                
            } else {
                char temp[100];
                strcpy(temp,directory);
                strcat(temp,limiter());
                strcat(temp,lsdir->d_name);
                push(directoriesActual,lsdir->d_name); 
                
            }

        }
    }

    closedir(dir);

    orderByDirectory(directoriesActual);


    for (i = 0; i < length(directoriesActual); i++) {
        
        char temp[100];
        strcpy(temp,directory);
        strcat(temp,limiter());
        strcat(temp,getValueStr(directoriesActual,i));
        if(is_dir(temp)) {
            printf ("%d - %s/\n", i+1, getValueStr(directoriesActual,i));
        } else {
            printf ("%d - %s\n", i+1, getValueStr(directoriesActual,i));
        }

    }

    printf("- Digite 0 para voltar a pasta.\n");

    //Select directory
    int selected;
    printf("\nDigite o número equivalente ao arquivo ou diretório: ");
    scanf("%d", &selected);

    if(selected != 0) {
        char * selectedName = (char *)getValue(directoriesActual,selected-1);
        char newDir[500];
        strcpy(newDir,directory);
        strcat(newDir,limiter());
        strcat(newDir, selectedName);
        destroyList(directoriesActual);

        if(is_dir(newDir)) {
            return chooseFile(newDir,filter);
        } else if(is_file(newDir)) {
            char * dir = (char *) malloc(strlen(newDir)* sizeof(char));
            strcpy(dir,newDir);
            return dir;
        }

    } else {
        char newDir[500];
        strcpy(newDir,directory);
        strcat(newDir,limiter());
        strcat(newDir, "..");
        destroyList(directoriesActual);
        return chooseFile(newDir,filter);
    }
    
}

void clear(){
    #ifdef WIN32
		system("CLS");
	#else
		system("clear");
	#endif
}

char * limiter(){
    #ifdef WIN32
        return "\\";
    #else
        return "/";
    #endif
}

bool is_file(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool is_dir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

void orderByDirectory(List * listDir) {
	//Ordenacao usando BubbleSort
	int i,n;
	void * aux;
	for (i = 0; i < length(listDir); i++){
		for (n = 0; n < length(listDir) -1; n++) {
			if(!(is_dir((char *)getValue(listDir,n)) && !is_dir((char *) getValue(listDir,n+1)))) {
				aux = getValue(listDir,n);
				setItem(listDir, n, getValue(listDir,n+1));
				setItem(listDir,n+1, aux);
			}
		}

	}

}