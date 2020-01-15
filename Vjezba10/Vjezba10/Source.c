#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>




typedef struct Cvor* NPoz;
typedef struct Stog* SPoz;

struct Cvor
{
	char* El;
	NPoz Desno;
	NPoz Lijevo;


};

struct Stog
{

	NPoz CvorEl;
	SPoz Next;
};


void StvoriNoviCvor(SPoz*);
void StvoriStablo(char*, SPoz, NPoz);
void StvoriCvorStablo(NPoz*);
void Pop(SPoz, NPoz*);
void Push(SPoz, NPoz);
void Print(NPoz);



int main()
{

	char* filename = NULL;
	SPoz stog = NULL;
	NPoz root = NULL;


	StvoriNoviCvor(&stog);

	filename = (char*)malloc(sizeof(char) * 128);
	memset(filename, '\0', 128);
	puts("Unesite ime dat za citanje");
	scanf("%s", filename);

	if (strrchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	StvoriStablo(filename, stog, &root);
	Print(root);


	return 0;
}


void StvoriNoviCvor(SPoz* S)
{
	SPoz q = NULL;

	q = (SPoz)malloc(sizeof(struct Stog));

	q->CvorEl = NULL;
	q->Next = NULL;
	*S = q;

}


void StvoriCvorStablo(NPoz* N)
{
	NPoz q = NULL;

	q = (NPoz*)malloc(sizeof(struct Cvor));

	q->El = NULL;
	q->Desno = NULL;
	q->Lijevo = NULL;

	*N = q;
}


void StvoriStablo(char* filename, SPoz stog, NPoz* root)
{

	int broj = 0;
	int NCount = 0;
	char* buff = NULL;
	NPoz q = NULL;
	FILE* fp = NULL;

	buff = (char*)malloc(sizeof(char) * 128);

	memset(buff, '\0', 128);
	fp = fopen(filename, "r");

	while (!feof(fp))
	{
		memset(buff, '\0', 128);

		StvoriCvorStablo(&q);

		fscanf(fp, "%s", buff);

		NCount = strlen(buff);

		NCount++;

		q->El = (char*)malloc(sizeof(char) * NCount);


		memset(q->El, '\0', NCount);
		NCount--;

		strcpy(q->El, buff, NCount);
		q->Desno = NULL;
		q->Lijevo = NULL;

		NCount = sscanf(buff, "%d", &broj);
		if (NCount == EOF || NCount <= 0)
		{
			Pop(stog, &q->Desno);
			Pop(stog, &q->Lijevo);
		}

		Push(stog, q);

	}

	fclose(fp);

	free(buff);

	Pop(stog, &q);
	*root = q;



}


void Pop(SPoz S, NPoz* element)
{
	SPoz tmp = NULL;
	NPoz q = NULL;

	tmp = S->Next;

	S->Next = tmp->Next;
	q = tmp->CvorEl;
	free(tmp);
	*element = q;
}

void Push(SPoz S, NPoz N)
{
	SPoz q = NULL;

	StvoriNoviCvor(&q);

	q->CvorEl = N;
	q->Next = S->Next;
	S->Next = q;
}


void Print(NPoz P)
{
	FILE* fp = NULL;

	fp = fopen("file1.txt", "w");



	if (P != NULL)
	{
		Print(P->Lijevo);
		Print(P->Desno);
		printf("%s", P->El);
		puts("");
	}

	if (P != NULL)
	{
		printf("%s", P->El);
		Print(P->Lijevo);
		Print(P->Desno);
		puts("");
	}

	if (P != NULL)
	{
		if (P->Lijevo != NULL)
			fprintf(fp, "(");
		Print(P->Lijevo);
		fprintf(fp, "%s", P->El);
		Print(P->Desno);
		if (P->Desno != NULL)
			fprintf(fp, ")");
	}

}

