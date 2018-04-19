#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define BLQ 50

int estaEn(char,char*);
void impLisPal(char*,char**,int);

int main(){
	char* dir = "/home/pi/Documents/PracticasC/STring/palabras2";
	char* dir2 = "/home/pi/Documents/PracticasC/STring/palabrasSeparadas";
	char* buff = calloc(BLQ,sizeof(char));
	char** db;
	char del[]= " ,.-;:_΅+`*^\n\t";
	int i;
	char c;
	int cl = 0;
	int cp = 0;
	FILE * f = fopen(dir,"r");
	while (!feof(f))
	{	
		if(1!=fread(&c,sizeof(char),1,f)){
			if (feof(f)) perror("Encontrado EOF");
			else if (ferror(f)) perror("Error del fichero");
		}else if(estaEn(c,del)){
			if(cl != 0){
				db = realloc(db,sizeof(char*)*(cp+1));
				db[cp] = malloc(sizeof(char)*(cl+1));
				strncpy(db[cp],buff,cl+1);
				cp++;
				cl = 0;
			}
		} else{
			buff[cl] = (char)c;
			buff[cl+1] = '\0';
			cl++;
		}	
	} 
	fclose(f);
	printf("\nSe han leido: %d palabras.\n\n",cp);
	for (i = 0; i < cp; i++){
		printf("%d:\t%s\n",strlen(db[i]),db[i]);
	}
	printf("\n\n");
	impLisPal(dir2,db,cp);
	printf("Escritura completada.\n\n");
	return 0;
}

int estaEn(char car,char* str){
	int r = 0;
	char *aux = str;
	while((r == 0)&&(*aux != '\0')){
		if(car == *aux) r = 1;
		aux++;
	}
	return r;
}

void impLisPal(char* __d, char** __l, int __t){
	FILE* fout = fopen(__d,"w+");
	int i;
	char cr = '\n';
	char *ptr;
	for(i = 0; i < __t; i++){
		if(i != 0){
			ptr = &cr;
			fwrite(ptr,sizeof(char),1,fout);
		}
		ptr = __l[i];
		while(*ptr != '\0'){
			fwrite(ptr,sizeof(char),1,fout);
			ptr++;
		}
	}
	fclose(fout);
}
