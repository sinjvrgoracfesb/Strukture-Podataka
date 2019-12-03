#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct lista {

	int x;
	struct lista *next;

}lista;


int random(void);
lista* pushstog(lista*);
lista* popstog(lista*);
lista* pushred(lista*);
lista* popred(lista*);
void print(lista*);

int main() {

	int i;

	lista* listahead = NULL;
	lista* redhead = NULL;
	


	 while(1){
		 printf("\nza odabir funkcije odaberite sljedeci broj:::\n 1.push stoga\n2.pop stog\n3.push red\n4.pop red\n5.izlaz\n:::");
		 scanf(" %d",&i);
		 puts("");
		 if (i == 1) {
			 listahead = pushstog(listahead);
			 print(listahead);
		 }
		 else if (i == 2) {
			 listahead = popstog(listahead);
			 print(listahead);
		 }
		 else if (i == 3) {

			 redhead = pushred(redhead);
			 print(redhead);
		 }
		 else if (i == 4) {
			 redhead = popred(redhead);
			 print(redhead);
		 }
		 else if (i == 5)
			 break;
		 else
			 printf("krivi unos pokusajte ponovno\n");
		
	 }

	 
	 scanf(" %d",&i);
	return 1;
}

int random(void) {
	int x;

	srand(time(NULL));

	x = (rand() % (100 - 10)) + 10;
	return x;
}
lista* pushstog(lista* head) {

	lista* p = NULL;

	p = (lista*)malloc(sizeof(lista));
	p->next = NULL;
	p->x = random();
	if (head == NULL) {
		head = p;

	}
	else {
		p->next = head;
		head = p;
	}
	return head;
}
lista* popstog(lista* head) {
	lista* brisi = NULL;
	lista *p= NULL;

	brisi = head;
	head = head -> next;
	free(brisi);


	return head;
}

lista* pushred(lista* head) {
	lista* p = NULL;
	lista*q = NULL;
	q = head;
	p = (lista*)malloc(sizeof(lista));
	p->next = NULL;
	p->x = random();
	if (head == NULL) {
		head = p;

	}
	else {
		while (q->next != NULL) {
			q = q->next;
		}
		q->next = p;
	
	}

	return head;
}

lista*popred(lista* head) {
	
	lista* brisi = NULL;
	lista *p = NULL;

	brisi = head;
	head = head->next;
	free(brisi);


	return head;
}
void print(lista* head) {

	lista*p = head;

	while (p != NULL) {
		printf("%d ",p->x);
		p = p->next;
	}
}

