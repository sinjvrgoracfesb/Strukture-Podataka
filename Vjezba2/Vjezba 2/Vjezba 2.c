#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<string.h>


typedef struct osoba {

	char ime[50];
	char prezime[50];
	int godina_rodenja;
	struct osoba *Next;



}osoba;

osoba *stvorilistu(int n)
{
	int i = 0;

	osoba *tmp = NULL;
	osoba *p = NULL;
	osoba *head = NULL;

	for (i = 0; i < n; i++)
	{
		tmp = (osoba *)malloc(sizeof(osoba));
		printf("Unesite pod za %d listu:\n", i + 1);
		scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->godina_rodenja);
		tmp->Next = NULL;

		if (head == NULL)
			head = tmp;
		else
		{
			p = head;
			while (p->Next != NULL)
				p = p->Next;
			p->Next = tmp;

		}



	}

	return head;
}

osoba * dodaj(osoba *Head)
{
	osoba *p = NULL;
	osoba *tmp = NULL;
	p = Head;
	//p = p->Next;
	tmp = (osoba*)malloc(sizeof(osoba));
	printf("Unesite novu osobu\n");
	scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->godina_rodenja);

	Head = tmp;
	tmp->Next = p;

	return Head;
}

void trazi(osoba *Head)
{
	char a[50];
	osoba *p = NULL;
	p = Head;
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
	//printf("Prezime je %s", a);

}

osoba* brisi(osoba *Head)
{
	int z;
	int i = 0;
	osoba*p = NULL;
	osoba *tmp = NULL;
	printf("Koji element zelite izbrisati:\n");
	scanf("%d", &z);
	p = Head;

	if (z == 0) {

		tmp = Head;
		Head = Head->Next;
		free(tmp);

	}

	else{
		for (i = 0; i < z-1; i++) {
			p = p->Next;
		}
		tmp = p->Next;
		p->Next = p->Next->Next;
		free(tmp);


		}
	
	return Head;

}




void ispisilistu(osoba *head)
{
	osoba*p = head;

	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->godina_rodenja);
		p = p->Next;


	}

}


osoba *dodaj_na_kraj(osoba *Head)
{
	osoba*p = NULL;
	osoba *tmp = NULL;
	tmp = (osoba*)malloc(sizeof(osoba));
	printf("Unesite novu osobu\n");
	scanf("%s %s %d", tmp->ime, tmp->prezime, &tmp->godina_rodenja);
	tmp->Next = NULL;
	p = Head;
	while (p->Next!= NULL)
	{		
		p = p->Next;
	}

	p->Next = tmp;

	return Head;
}



int main()
{
	int i;
	int n = 0;

	osoba *HEAD = NULL;
	osoba *pret = NULL;
	printf("Koliko osoba zelite:\n");
	scanf("%d", &n);

	HEAD = stvorilistu(n);
	printf("\n");
	ispisilistu(HEAD);
	printf("\n");
	HEAD = dodaj(HEAD);
	printf("\n");
	ispisilistu(HEAD);
	printf("\n");
	trazi(HEAD);
	printf("\n");
	HEAD=brisi(HEAD);
	printf("\n");
	ispisilistu(HEAD);

	HEAD = dodaj_na_kraj(HEAD);
	printf("\n");
	ispisilistu(HEAD);





	scanf("%d", &i);
	return 0;
}