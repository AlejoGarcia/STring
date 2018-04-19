#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define BLQ 50
#define DELI " ,.-;:_΅+`*^\n\t"
#define DIR1 "/home/pi/Documents/PracticasC/STring/palabras2"
#define DIR2 "/home/pi/Documents/PracticasC/STring/palabrasSeparadas"

int estaEn(char __car, char* __str);
void guardarLista(char* __d, char** __l, int __t);
int cargarLista(char* __dir, char ** __dest, char* __sep);

int main(void)
{
	char** db = NULL;
	int i;
	int cp = cargarLista(DIR1, db, DELI); 
	printf("\nSe han leido: %d palabras.\n\n",cp);
	for (i = 0; i < cp; i++) printf("%d:\t%s\n",strlen(db[i]),db[i]);
	printf("\n\n");
	guardarLista(DIR2,db,cp);
	printf("Escritura completada.\n\n");
	return 0;
}

int estaEn(char __car, char* __str)
{
	int r = 0;
	char *__aux = __str;
	while((r == 0)&&(*__aux != '\0')){
		if(__car == *__aux) r = 1;
		__aux++;
	}
	return r;
}

void guardarLista(char* __d, char** __l, int __t)
{
	FILE * fout = fopen(__d,"w+");
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

int cargarLista(char* __dir, char ** __dest, char* __sep)
{	
	FILE * fin = fopen(__dir,"r");
	char* buff = calloc(BLQ,sizeof(char));
	char aux;
	int clet = 0;
	int cpal = 0;
	while (!feof(fin))
	{	
		if(1!=fread(&aux,sizeof(char),1,fin)){
			if (feof(fin)) perror("Encontrado EOF");
			else if (ferror(fin)) perror("Error del fichero");
		}else if(estaEn(aux,__sep)){
			if(clet != 0){
				__dest = realloc(__dest,sizeof(char*)*(cpal+1));
				__dest[cpal] = malloc(sizeof(char)*(clet+1));
				strncpy(__dest[cpal],buff,clet+1);
				cpal++;
				clet = 0;
			}
		} else{
			buff[clet] = (char)aux;
			clet++;
			buff[clet] = '\0';
		}	
	} 
	fclose(fin);
	return cpal;
}
