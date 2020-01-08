#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


struct Cvor;
typedef struct Cvor CVOR;
typedef struct Cvor* Poz;

struct Cvor
{
    int El;
    Poz Desno;
    Poz Lijevo;
};

Poz UmetniBroj(Poz, int);
void Print(Poz);
Poz Obrisi(Poz, int);
Poz Najmanji(Poz);
void Pronadji(Poz, int);


int main()
{

    int izbor = 1, broj = 0;

    Poz root = NULL;


    while (izbor)
    {
        puts("Unesite izbor:1-unos elementa, 2-print. 3-obrisati element, 4-pronaci element, 5-exit");

        scanf("%d", &izbor);

        switch (izbor)
        {
        case 1:
            puts("Odraberite broj");
            scanf("%d", &broj);
            root = UmetniBroj(root, broj);
            break;

        case 2:
            puts("Elementi su:");
            Print(root);
            break;

        case 3:
            puts("Unesite broj koji zelite obristai:");
            scanf("%d", &broj);

            root = Obrisi(root, broj);
            break;

        case 4:
            puts("Unesite broj koji zelite pronaci:");
            scanf("%d", &broj);
            Pronadji(root, broj);
            break;

        case 5:
            izbor = 0;
            break;

        default:
            printf("Kriva naredba\n");
            break;
        }
    }

    return 0;
}




Poz UmetniBroj(Poz P, int n)
{
    if (P == NULL)
    {
        P = (Poz)malloc(sizeof(struct Cvor));

        P->El = n;
        P->Desno = NULL;
        P->Lijevo = NULL;
    }

    else if (P->El < n)
        P->Desno = UmetniBroj(P->Desno, n);
    else if (P->El > n)
        P->Lijevo = UmetniBroj(P->Lijevo, n);

    return P;

}

void Print(Poz P)
{
    if (P != NULL)
    {
        printf(" %d", P->El);
        Print(P->Lijevo);
        Print(P->Desno);
    }
}



Poz Obrisi(Poz P, int n)
{

    Poz tmp = NULL;

    if (P->El > n)
        P->Lijevo = Obrisi(P->Lijevo, n);
    else if (P->El < n)
        P->Desno = Obrisi(P->Desno, n);
    else
    {
        if (P->Desno != NULL && P->Lijevo != NULL)
        {
            tmp = Najmanji(P->Desno);
            P->El = tmp->El;
            P->Desno = Obrisi(P->Desno, tmp->El);

        }

        else
        {
            tmp = P;
            if (P->Lijevo == NULL)
                P = P->Desno;
            else
                P = P->Lijevo;

            free(tmp);
        }


    }


    return P;
}


Poz Najmanji(Poz P)
{
    if (P != NULL && P->Lijevo != NULL)
        return Najmanji(P->Lijevo);

    return P;
}

void Pronadji(Poz P, int n)
{
    if (P->El < n)
        Pronadji(P->Desno, n);
    else if (P->El > n)
        Pronadji(P->Lijevo, n);
    else if (P->El == n)
        puts("Element je pronaden");
    else
        puts("Taj element ne postoji");

}
