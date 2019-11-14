#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include<malloc.h>


typedef struct Lista *Pozicija;

typedef struct Lista
{
	int x;
	Pozicija Next;


}Lista;


void StvoriListu(Pozicija *);
void IspisiListu(Pozicija);
void CitajIzDatoteke(Pozicija);
void UnijaLista(Pozicija, Pozicija, Pozicija);
void PresjekLista(Pozicija, Pozicija, Pozicija);

int main()
{
	int i;

	Lista L1, L2, U, P;

	L1.Next = NULL;
	L2.Next = NULL;
	U.Next = NULL;
	P.Next = NULL;

	CitajIzDatoteke(&L1);
	puts("Prva lista sadrzi elemente:");
	IspisiListu(L1.Next);

	CitajIzDatoteke(&L2);
	puts("Druga lista sadrzi elemente:");
	IspisiListu(L2.Next);

	UnijaLista(L1.Next, L2.Next, &U);
	puts("Unija elemenata je:");
	IspisiListu(U.Next);

	PresjekLista(L1.Next, L2.Next, &P);
	puts("Presjek elemenata je:");
	IspisiListu(P.Next);


	scanf("%d", &i);
	return 0;
}



void StvoriListu(Pozicija *head)
{
	Pozicija tmp = NULL;

	*head = (Pozicija)malloc(sizeof(Lista));

	tmp = *head;
	tmp->Next = NULL;

}

void IspisiListu(Pozicija P)
{
	Pozicija tmp = NULL;

	while (P != NULL)
	{
		printf("%d ", P->x);
		P = P->Next;
	}
	printf("\n");
}

void CitajIzDatoteke(Pozicija P)
{
	FILE *fp = NULL;
	char *filename;
	Pozicija q = NULL;
	Pozicija tmp = NULL;

	filename = (char *)malloc(sizeof(char) * 128);

	puts("Unesite ime datoteke za citanje liste:");
	scanf("%s", filename);

	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	fp = fopen(filename, "r");

	while (!feof(fp))
	{
		StvoriListu(&q);

		fscanf(fp, "%d", &q->x);

		tmp = P;

		while (tmp->Next != NULL && tmp->Next->x > q->x)
			tmp = tmp->Next;

		q->Next = tmp->Next;
		tmp->Next = q;



	}

	fclose(fp);

}


void UnijaLista(Pozicija L1, Pozicija L2, Pozicija L3)
{
	Pozicija q = NULL;
	Pozicija tmp = NULL;

	while (L1 != NULL && L2 != NULL)
	{
		StvoriListu(&q);

		if (L1->x > L2->x)
		{
			q->x = L1->x;
			L1 = L1->Next;
		}

		else if (L2->x > L1->x)
		{
			q->x = L2->x;
			L2 = L2->Next;
		}

		else
		{
			q->x = L2->x;
			L2 = L2->Next;
			L1 = L1->Next;
		}

		if (L3->x == q->x)
			free(q);

		else
		{

			q->Next = L3->Next;
			L3->Next = q;

			L3 = q;

		}
	}

	if (L1 == NULL)
		tmp = L2;
	else
		tmp = L1;

	while (tmp != NULL)
	{
		StvoriListu(&q);

		q->x = tmp->x;

		if (L3->x == q->x)
			free(q);

		else
		{
			q->Next = L3->Next;
			L3->Next = q;

			L3 = q;
		}

		tmp = tmp->Next;

	}

}


void PresjekLista(Pozicija L1, Pozicija L2, Pozicija L3)
{
	Pozicija q = NULL;
	Pozicija tmp = NULL;


	while (L1 != NULL && L2 != NULL)
	{


		if (L1->x > L2->x)
			L1 = L1->Next;
		else if (L2->x > L1->x)
			L2 = L2->Next;
		else {

			StvoriListu(&q);

			q->x = L1->x;

			q->Next = L3->Next;
			L3->Next = q;

			L3 = q;

			L1 = L1->Next;
			L2 = L2->Next;

		}

	}


}