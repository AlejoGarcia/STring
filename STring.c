#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define BLQ 50

int main(){
	char* dir = "/home/pi/Documents/PracticasC/palabras";
	//char* dir2 = "/home/pi/Documents/PracticasC/palabrasSeparadas";
	char* buff = calloc(BLQ,sizeof(char));
	char** db;
	int i;
	char c;
	int cl = 0;
	int cp = 0;
	FILE * fi = fopen(dir,"r");
	while (!feof(f))
	{	
		fread(&c,sizeof(char),1,f);
		if(!(islower(c)||isupper(c)||isdigit(c)||(cl == 0))){
			db = realloc(db,sizeof(char*)*(cp+1));
			db[cp] = malloc(sizeof(char)*(cl+1));
			strncpy(db[cp],buff,cl);
			strcat(db[cp],"\0");
			cp++;
			cl = 0;
		}else if((c!='.')&&(c!='-')&&(c!='\n')&&(c!=',')){
			buff[cl] = (char)c;
			cl++;
		}	
	} 
	fclose(f);
	printf("\nSe han leido: %d palabras.\n\n",cp);
	for (i = 0; i < cp; i++){
		printf("%d:\t%s\n",strlen(db[i]),db[i]);
	}
	printf("\n\n");
	return 0;
}
