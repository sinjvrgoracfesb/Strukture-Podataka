#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include<stdlib.h>




struct Cvor;
typedef struct Cvor CVOR;
typedef struct Cvor* Pozicija;


struct Cvor
{
	float el;
	Pozicija Next;
}Cvor;


void CreateNew(Pozicija*);
void Push(Pozicija, float);
void Pop(Pozicija, float*);
void Kalkulator(float, float, char*, float*);
void Postfix(char*, Pozicija);
int JeLiOperand(char*, float*);


int main()
{
	CVOR Stog;

	Stog.Next = NULL;

	char* filename = NULL;

	filename = (char*)malloc(sizeof(char) * 128);
	printf("Unesite ime datoteke:");
	scanf("%s", filename);

	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	Postfix(filename, &Stog);


	printf("Rezultat: %.2f", Stog.Next->el);


	
	return 0;
}


void StvoriCvor(Pozicija* head)
{
	Pozicija tmp = NULL;

	*head = (Pozicija)malloc(sizeof(CVOR));

	tmp = *head;
	tmp->Next = NULL;

}

void IspisiCvor(Pozicija P)
{
	Pozicija tmp = NULL;

	while (P != NULL)
	{
		printf("%f ", P->el);
		P = P->Next;
	}
	printf("\n");
}

void Push(Pozicija P, float x)
{

	Pozicija q = NULL;

	StvoriCvor(&q);

	q->el = x;

	q->Next = P->Next;
	P->Next = q;

}
void Pop(Pozicija P, float* x)
{
	Pozicija tmp = NULL;

	tmp = P->Next;

	P->Next = tmp->Next;
	*x = tmp->el;
	free(tmp);

}



void Postfix(char* FileName, Pozicija S)
{
	float num = 0, operand1 = 0, operand2 = 0;
	char* buff = NULL;
	FILE* fp = NULL;

	buff = (char*)malloc(sizeof(char) * 128);

	fp = fopen(FileName, "r");

	while (!feof(fp))
	{
		fscanf(fp, " %s", buff);
		if (strlen(buff) == 0) continue;

		if (JeLiOperand(buff, &num))
		{
			Pop(S, &operand2);
			Pop(S, &operand1);
			Kalkulator(operand1, operand2, buff, &num);
		}

		Push(S, num);
	}



	fclose(fp);

}


void Kalkulator(float x, float y, char* operacija, float* rezultat)
{
	if (strcmp(operacija, "+") == 0)
		*rezultat = x + y;
	else if (strcmp(operacija, "-") == 0)
		*rezultat = x - y;
	else if (strcmp(operacija, "*") == 0)
		*rezultat = x * y;
	else if (strcmp(operacija, "/") == 0)
		*rezultat = x / y;

	else
	{
		*rezultat = 0;
	}
}


int JeLiOperand(char* buff, float* number)
{
	int rezultat;

	rezultat = sscanf(buff, "%f", number);
	if (rezultat == EOF || rezultat == 0 || rezultat != 1)return 1;

	return 0;
}