#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define VELICINA_TABLICE 11



struct _student;
typedef struct _student* Poz;
typedef struct _student
{
	int MB;
	char* ime;
	char* prezime;
	Poz Next;
} _STUDENT;

struct _hashCvor;
typedef struct _hashCvor* PHash;
typedef struct _hashCvor
{
	int hashValue;
	Poz tree;
}_HASHCVOR;


void CitajIzDatoteke(char*, PHash);
void UmetniHash(Poz, PHash);
void RacunajHash(Poz, int*, int);
Poz UmetniListu(Poz, Poz);
void StvoriCvor(Poz*);
void PrintHash(PHash, int);
void PrintList(Poz);




int main()
{
	char* filename = NULL;
	PHash HashTable = NULL;
	int hashIndex;

	filename = (char*)malloc(sizeof(char) * 128);

	memset(filename, '\0', 128);

	puts("Unesite ime datoteke");
	scanf("%s", filename);

	HashTable = (PHash)malloc(sizeof(_HASHCVOR) * VELICINA_TABLICE);

	hashIndex = 0;
	while (hashIndex < VELICINA_TABLICE)
	{
		HashTable[hashIndex].tree = NULL;
		hashIndex++;
	}

	CitajIzDatoteke(filename, HashTable);

	PrintHash(HashTable, VELICINA_TABLICE);



	return 0;
}



void CitajIzDatoteke(char* filename, PHash HashTable)
{
	FILE* fp = NULL;
	Poz q = NULL;
	char* buff = NULL;
	int bufflength = 0;
	int datacounter = 0;


	buff = (char*)malloc(sizeof(char) * 128);

	fp = fopen(filename, "r");

	while (!feof(fp))
	{

		memset(buff, '\0', 128);
		fscanf(fp, "%s", buff);

		bufflength = strlen(buff);

		if (datacounter % 3 == 0)
		{
			if (q != NULL)
				UmetniHash(q, HashTable);



			StvoriCvor(&q);

			sscanf(buff, "%d", &q->MB);

		}

		else if (datacounter % 3 == 1)
		{
			q->ime = (char*)malloc(sizeof(char) * (bufflength + 1));

			memset(q->ime, '\0', bufflength + 1);

			sscanf(buff, " %s", q->ime);


		}

		else if (datacounter % 3 == 2)
		{
			q->prezime = (char*)malloc(sizeof(char) * (bufflength + 1));

			memset(q->prezime, '\0', bufflength + 1);
			sscanf(buff, "%s", q->prezime);





		}

		datacounter++;

	}

	fclose(fp);

	UmetniHash(q, HashTable);


}


void UmetniHash(Poz q, PHash HashTable)
{

	int index = 0;

	RacunajHash(q, &index, VELICINA_TABLICE);

	if (HashTable[index].hashValue != index)
		HashTable[index].tree = NULL;

	HashTable[index].hashValue = index;
	HashTable[index].tree = UmetniListu(HashTable[index].tree, q);

}


Poz UmetniListu(Poz P, Poz q)
{
	Poz L = P;

	if (L == NULL)return q;


	if (L->Next == NULL && strcmp(L->prezime, q->prezime) < 0)
	{
		q->Next = L;
		return q;
	}

	while (L != NULL && strcmp(L->prezime, q->prezime) > 0)
		L = L->Next;



	if (L != NULL && strcmp(L->prezime, q->prezime) == 0)
	{
		while (L->Next != NULL && strcmp(L->prezime, q->prezime) == 0 && strcmp(L->ime, q->ime) < 0)
			L = L->Next;


		if (L->Next != NULL && strcmp(L->prezime, q->prezime) == 0 && strcmp(L->ime, q->ime) == 0)
			while (L->Next != NULL && strcmp(L->prezime, q->prezime) == 0 && strcmp(L->ime, q->ime) == 0 && L->MB < q->MB)
				L = L->Next;





	}

	q->Next = L->Next;
	L->Next = q;

	return P;
}


void RacunajHash(Poz q, int* index, int velicinatablice)
{
	int buffLength = 0;
	int charIndex = 0;
	int sum = 0;

	buffLength = strlen(q->prezime);

	while (charIndex < buffLength && charIndex < 5)
	{
		sum += (int)q->prezime[charIndex];
		charIndex++;
	}


	*index = sum % velicinatablice;

}


void StvoriCvor(Poz* q)
{
	Poz tmp = NULL;

	tmp = (Poz)malloc(sizeof(_STUDENT));

	tmp->Next = NULL;

	*q = tmp;
}

void PrintHash(PHash HashTable, int velicinatablice)
{
	int hashindex = 0;

	printf("Sadrzaj hash tablice:\n");
	while (hashindex < velicinatablice)
	{
		printf("Kljuc (%d) data:", HashTable->hashValue);
		PrintList(HashTable->tree);
		HashTable++;
		hashindex++;
	}



}

void PrintList(Poz P)
{
	int i = 0;
	while (P != NULL)
	{
		printf("%d %s %s", ++i, P->ime, P->prezime);
		P = P->Next;
	}


}