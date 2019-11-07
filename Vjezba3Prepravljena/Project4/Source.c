#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<string.h>


typedef struct osoba {

	char ime[50];
	char prezime[50];
	int godina_rodenja;
	struct osoba* Next;



}osoba;

osoba* stvorilistu(int n, osoba* head)
{
	int i = 0;

	osoba* tmp = NULL;
	osoba* p = NULL;
	head = (osoba*)malloc(sizeof(osoba));

	for (i = 0; i < n; i++)
	{
		tmp = (osoba*)malloc(sizeof(osoba));
		printf("Unesite pod za %d listu:\n", i + 1);
		scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->godina_rodenja);
		tmp->Next = NULL;

		if (i == 0) {

			head->Next = tmp;
		}

		else {
			p = head;
			while (p->Next != NULL) {
				p = p->Next;
			}

			p->Next = tmp;

		}

	}

	return head;
}

osoba* dodaj_na_pocetak(osoba* Head)
{
	osoba* p = NULL;
	osoba* tmp = NULL;
	p = Head->Next;

	tmp = (osoba*)malloc(sizeof(osoba));
	printf("Unesite novu osobu na pocetak\n");
	scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->godina_rodenja);

	Head->Next = tmp;

	tmp->Next = p;

	return Head;
}

void trazi_po_prezimenu(osoba* Head)
{
	char a[50];
	osoba* p = NULL;
	p = Head->Next;
	printf("Unesite prezime\n");
	scanf("%s", a);
	while (p != NULL)
	{
		if (strcmp(a, p->prezime) == 0)
		{
			printf("Prezime je pronadeno\n");
			break;

		}

		p = p->Next;

	}


}

osoba* brisi(osoba* Head)
{
	int z;
	int i = 0;
	osoba* p = NULL;
	osoba* tmp = NULL;
	printf("Koji element zelite izbrisati:\n");
	scanf("%d", &z);
	p = Head->Next;

	if (z == 1) {
		tmp = Head->Next;
		Head->Next = Head->Next->Next;
		free(tmp);

	}

	else {
		for (i = 0; i < z - 2; i++) {
			p = p->Next;
		}
		tmp = p->Next;
		p->Next = p->Next->Next;
		free(tmp);


	}

	return Head;

}

osoba* dodaj_ispred_odredenog_elementa(osoba* Head) {

	int z;
	int i = 0;
	osoba* p = NULL;
	osoba* tmp = NULL;
	osoba* q = NULL;
	printf("ispred koje osobe  zelite dodati novu osobu::\n");
	scanf("%d", &z);
	p = Head->Next;
	tmp = (osoba*)malloc(sizeof(osoba));
	printf("Unesite novu osobu\n");
	printf("\n");
	scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->godina_rodenja);
	printf("\n");

	if (z == 1)
	{
		Head->Next = tmp;
		tmp->Next = p;
	}

	else
	{
		for (i = 0; i < z - 1; i++)
		{
			q = p;
			p = p->Next;
		}
		q->Next = tmp;
		tmp->Next = p;
	}



	return Head;
}

osoba* dodaj_iza_odredenog_elementa(osoba* Head) {

	int z;
	int i = 0;
	osoba* p = NULL;
	osoba* tmp = NULL;
	printf("\n");
	printf("iza kojeg mjesta zelite dodati istu::\n");
	scanf("%d", &z);
	p = Head->Next;
	tmp = (osoba*)malloc(sizeof(osoba));
	printf("Unesite novu osobu\n");
	scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->godina_rodenja);

	for (i = 0; i < z - 1; i++) {
		p = p->Next;
	}

	tmp->Next = p->Next;
	p->Next = tmp;



	return Head;
}

void ispisilistu(osoba* p)
{

	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->godina_rodenja);
		p = p->Next;


	}

}


osoba* dodaj_na_kraj(osoba* Head)
{
	osoba* p = NULL;
	osoba* tmp = NULL;
	tmp = (osoba*)malloc(sizeof(osoba));
	printf("Unesite novu osobu na kraj\n");
	scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->godina_rodenja);
	printf("\n");
	tmp->Next = NULL;
	p = Head;
	while (p->Next != NULL)
	{
		p = p->Next;
	}

	p->Next = tmp;

	return Head;
}

void soritiraj_po_prez(osoba* Head)
{

	osoba* tmp = NULL;
	osoba* j = NULL;
	osoba* prev_j = NULL;
	osoba* end = NULL;
	osoba* p = Head;

	while (p->Next != end)
	{
		prev_j = p;
		j = prev_j->Next;
		while (j->Next != end)
		{
			if (strcmp(j->prezime, j->Next->prezime) > 0)
			{
				tmp = j->Next;
				prev_j->Next = tmp;
				j->Next = tmp->Next;
				tmp->Next = j;

				j = tmp;

			}
			prev_j = j;
			j = j->Next;
		}
		end = j;
	}
}


void Upis_U_Datoteku(osoba* p)

{

	FILE* fp;


	fp = fopen("Osoba.txt", "w");

	while (p != NULL)
	{
		fprintf(fp, "%s %s %d\n", p->ime, p->prezime, p->godina_rodenja);
		p = p->Next;

	}

	fclose(fp);

}



void Ispis_Iz_Datoteke(osoba* P)
{

	FILE* fp;
	osoba* tmp = P;
	fp = fopen("Osoba.txt", "r");

	while (!feof(fp) && P != NULL)
	{
		fscanf(fp, "%s %s %d", P->ime, P->prezime, &P->godina_rodenja);
		P = P->Next;


	}

	P = tmp;
	while (P != NULL) {
		printf("%s %s %d\n", P->ime, P->prezime, P->godina_rodenja);
		P = P->Next;
	}

	fclose(fp);
	return;
}


int main()
{
	int i;
	int n = 0;

	osoba* HEAD = NULL;

	printf("Koliko osoba zelite:\n");
	scanf("%d", &n);

	HEAD = stvorilistu(n, HEAD);
	printf("\n");
	ispisilistu(HEAD->Next);
	printf("\n");

	HEAD = dodaj_na_pocetak(HEAD);
	printf("\n");
	ispisilistu(HEAD->Next);
	printf("\n");

	trazi_po_prezimenu(HEAD);
	printf("\n");

	HEAD = brisi(HEAD);
	printf("\n");
	ispisilistu(HEAD->Next);

	HEAD = dodaj_na_kraj(HEAD);
	ispisilistu(HEAD->Next);
	printf("\n");

	HEAD = dodaj_ispred_odredenog_elementa(HEAD);
	printf("\n");
	ispisilistu(HEAD->Next);
	printf("\n");

	HEAD = dodaj_iza_odredenog_elementa(HEAD);
	printf("\n");
	ispisilistu(HEAD->Next);
	printf("\n");

	printf("Osobe po prezimenu su:\n ");
	soritiraj_po_prez(HEAD);
	ispisilistu(HEAD->Next);

	Upis_U_Datoteku(HEAD->Next);
	printf("\n\n***Ucitane osobe iz datoteke:\n");
	Ispis_Iz_Datoteke(HEAD->Next);




	scanf("%d", &i);
	return 0;
}