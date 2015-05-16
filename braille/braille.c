#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int braille_to_char[64]= {0};
char * lines[3];
int length[3];

#define ADD_ENTRY(LOC,VAL)  braille_to_char[LOC] = VAL;
#define GET_VAL(VAL) braille_to_char[VAL]
							
void fill_braille_array()
{
	ADD_ENTRY(1,'A')
	ADD_ENTRY(5,'B')
	ADD_ENTRY(3,'C')
	ADD_ENTRY(11,'D')
	ADD_ENTRY(9,'E')
	ADD_ENTRY(7,'F')
	ADD_ENTRY(15,'G')
	ADD_ENTRY(13,'H')
	ADD_ENTRY(6,'I')
	ADD_ENTRY(14,'J')
	ADD_ENTRY(7,'K')
	ADD_ENTRY(21,'L')
	ADD_ENTRY(19,'M')
	ADD_ENTRY(27,'N')
	ADD_ENTRY(25,'O')
	ADD_ENTRY(23,'P')
	ADD_ENTRY(31,'Q')
	ADD_ENTRY(29,'R')
	ADD_ENTRY(22,'S')
	ADD_ENTRY(30,'T')
	ADD_ENTRY(49,'U')
	ADD_ENTRY(53,'V')
	ADD_ENTRY(46,'W')
	ADD_ENTRY(51,'X')
	ADD_ENTRY(59,'Y')
	ADD_ENTRY(57,'Z')
}

int get_math_rep(char *br_char)
{
	int i = 0;
	int val = 0;
	int ret = -1;
	char * cur = br_char;
	for(;i<6;i++)
	{
		if(cur[i] == 'O')
		{
			int temp = 1<<i;
			val|=temp;
		}
		else if (cur[i] == '.')
		{
			//do nothing
		}
		else 
		{
			printf("ERR : Invalid Char found ");
			val =-1;
		}
	}
	return val;
}

int get_braille_rep(char *fr , char *sc , char *thr)
{
	char braille_char[10]= {'\0'};
	strncat(braille_char,fr,2);
	strncat(braille_char,sc,2);
	strncat(braille_char,thr,2);
	return get_math_rep(&braille_char[0]);
}

int parse_braille()
{
	int i;
	for(i=0;i<length[0];i+=3)
	{
		char *first = 	lines[0];
		char *second = 	lines[1];
		char *third = 	lines[2];
		first+=i;second+=i;third+=i;
		int braille_rep = get_braille_rep(first,second,third);
		if(braille_rep == -1) return -1;
		printf("%c",GET_VAL(braille_rep));
	}
	printf("\n");
	return 0;
}

int main(int argc ,char **argv)
{
	fill_braille_array();
	FILE *fp = NULL;
	fp = fopen("braille.txt","r");
	if(fp == NULL) { printf("Err: No File braille.txt \n") ;return -1;}
	int i =0;
	while(1)
	{
		char *str = (char *)malloc(sizeof(char)*255) ;
		fgets(str,255,fp);
		lines[i] = &str[0];
		length[i] = strlen(lines[i]);
		i++;
		if (i ==3)break;
	}
	if((length[0] == length[1]) &&(length[1]== length[2]))
	{
		if(parse_braille() == -1) printf("Error encountered in transation !\n");
	}
	else
	{
		printf("Error : wrong braille syntax");
	}
	free(lines[0]);free(lines[1]);free(lines[2]);
	fclose(fp);
	return 0;
}
