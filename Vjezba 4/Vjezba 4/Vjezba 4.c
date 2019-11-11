#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<string.h>


typedef struct Polinom;
typedef struct Polinom *Pozicija;
typedef struct Polinom POLINOM;


typedef struct Polinom
{
	int koeficijent;
	int potencija;
	Pozicija Next;


}Polinom;

void StvoriListu(Pozicija *);
void IspisiListu(Pozicija);
void CitajIzDatoteke(Pozicija);
void SumaPolinoma(Pozicija, Pozicija, Pozicija);
void UmnozakPolinoma(Pozicija, Pozicija, Pozicija);

int main()
{
	int i;

	Polinom P1, P2, S, M;

	P1.Next = NULL;
	P2.Next = NULL;
	S.Next = NULL;
	M.Next = NULL;
	
	CitajIzDatoteke(&P1);
	printf("Polinom jedan je:");
	IspisiListu(P1.Next);

	printf("\n");

	CitajIzDatoteke(&P2);
	printf("Polinom dva je:");
	IspisiListu(P2.Next);

	printf("\n");

	SumaPolinoma(P1.Next, P2.Next, &S);
	printf("Suma polinoma je:");
	IspisiListu(S.Next);

	printf("\n");

	UmnozakPolinoma(P1.Next, P2.Next, &M);
	printf("Umnozak polinoma je:");
	IspisiListu(M.Next);


scanf("%d", &i);
return 0;
}


void StvoriListu(Pozicija *head)
{
	Pozicija tmp=NULL;

	*head=(Pozicija)malloc(sizeof(POLINOM));
	
	tmp=*head;
	tmp->Next=NULL;

}

void CitajIzDatoteke(Pozicija P)
{
	FILE *fp=NULL;
	char *filename=NULL;
	Pozicija q=NULL;
	Pozicija tmp=NULL;

	filename=(char *)malloc(sizeof(char)*50);

	printf("Unesite ime datoteke za citanje polinoma:");
	scanf(" %s", filename);

	if(strchr(filename, '.')==NULL)
		strcat(filename, ".txt");

	fp=fopen(filename, "r");

	while(!feof(fp))
	{	
		StvoriListu(&q);

		fscanf(fp, " %d %d", &q->koeficijent, &q->potencija);

		tmp=P;
		while(tmp->Next!=NULL && tmp->Next->potencija>q->potencija)
			tmp=tmp->Next;
		

		if(tmp->Next!=NULL && tmp->Next->potencija==q->potencija)
		{
			tmp->Next->koeficijent+=q->koeficijent;
			free(q);
			if(tmp->Next->koeficijent==0)
			{
				q=tmp->Next;
				tmp->Next=q->Next;
				free(q);
			}
		}

		else
		{
			q->Next=tmp->Next;
			tmp->Next=q;
		}
	
	
	
	}

	fclose(fp);


}

void IspisiListu(Pozicija P)
{
	
	while(P!=NULL)
	{
		printf("+%dx^%d", P->koeficijent, P->potencija);
		P=P->Next;
	
	}
	


}

void SumaPolinoma(Pozicija P1, Pozicija P2, Pozicija S)
{
	Pozicija q=NULL;
	Pozicija tmp=NULL;

	while(P1!=NULL && P2!=NULL)
	{
		StvoriListu(&q);

		if(P1->potencija > P2->potencija)
		{
			q->potencija=P1->potencija;
			q->koeficijent=P1->koeficijent;
			P1=P1->Next;
		
		}

		else if(P1->potencija < P2->potencija)
		{
			q->potencija=P2->potencija;
			q->koeficijent=P2->koeficijent;
			P2=P2->Next;
		
		}

		else
		{
			q->potencija=P1->potencija;
			q->koeficijent=P1->koeficijent+P2->koeficijent;
			P1=P1->Next;
			P2=P2->Next;
		
		}
	
		q->Next=S->Next;
		S->Next=q;

		S=q;
	}


}


void UmnozakPolinoma(Pozicija P1, Pozicija P2, Pozicija M)
{
	Pozicija q=NULL;
	Pozicija i=NULL;
	Pozicija j=NULL;
	Pozicija tmp=NULL;

	i=P1;

	while(i!=NULL)
	{
		j=P2;
		while(j!=NULL)
		{
			StvoriListu(&q);

			q->potencija=i->potencija+j->potencija;
			q->koeficijent=i->koeficijent*j->koeficijent;

			tmp=M;
			
			while(tmp->Next!=NULL && tmp->Next->potencija > q->potencija)
				tmp=tmp->Next;

			if(tmp->Next!=NULL && tmp->Next->potencija == q->potencija)
			{
				tmp->Next->koeficijent+=q->koeficijent;
				free(q);

				if(tmp->Next->koeficijent==0)
				{
					q=tmp->Next;
					tmp->Next=q->Next;

					free(q);
				
				}
			}
				
			else
			{
				q->Next=tmp->Next;
				tmp->Next=q;
				
			}

				j=j->Next;
			
			}
			i=i->Next;
		}
	
}