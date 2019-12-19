#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


struct Cvor;
typedef struct Cvor *Pozicija;

typedef struct Cvor
{
	char *ime;
	int isRoot;
	Pozicija Next;
	Pozicija Dijete;
};


struct Stog;
typedef struct Stog *Poz;

typedef struct Stog
{
	Pozicija Cvor;
	Poz Next;

};

void NoviCvor(Pozicija *);
void NoviStog(Poz *);
void PrintajPath(char *);
void PrintajDirektorij(Pozicija, char *);
Pozicija UpDirektorij(Pozicija, char *, Poz);
void Push(Poz, Pozicija);
int Pop(Poz, Pozicija *);
Pozicija InDirektorij(Pozicija, char *, char *, Poz);
void StvoriDirektorij(Pozicija, char *);
Pozicija UmetniDirektorij(Pozicija, Pozicija);
void Help();



int main()
{
	char *path = NULL;
	char *komanda = NULL;
	char *ImeDirektorija = NULL;
	char *upute = NULL;
	char *buff = NULL;
	int i=0;
	

	Pozicija root=NULL;
	Poz stog=NULL;
	Pozicija upDir=NULL;

	path=(char *)malloc(sizeof(char)*128);
	komanda=(char *)malloc(sizeof(char)*128);
	ImeDirektorija=(char *)malloc(sizeof(char)*128);
	upute=(char *)malloc(sizeof(char)*128);
	buff=(char *)malloc(sizeof(char)*128);

	NoviCvor(&root);

	puts("Napisi ime direktorija");
	scanf("%s", buff);

	root->ime=(char *)malloc(sizeof(char)*(strlen(buff)+1));

	memset(root->ime, '\0', sizeof(root->ime));
	memset(path, '\0', sizeof(path));
	memset(komanda, '\0', sizeof(path));

	sscanf(buff, "%s", root->ime);
	root->isRoot=1;
	root->Dijete=NULL;
	root->Next=NULL;
	upDir=root;

	NoviStog(&stog);

	stog->Next=NULL;

	strcat(path, root->ime);
	strcat(path, ":\\");

	while(strcmp(upute, "exit")!=0)
	{
		for(i!=0)
			PrintajPath(path);

		fgets(komanda, 1024, stdin);
		
		sscanf(komanda, "%s %s", upute, ImeDirektorija);

		if(strcmp(upute, "md")==0)
		{
			if(upDir==NULL)
				{
					puts("Error");
					break;
				}

			StvoriDirektorij(upDir, ImeDirektorija);	
		}

		else if(strcmp(upute, "dir")==0)
			PrintajDirektorij(upDir, path);

		else if(strcmp(upute, "cd..")==0)
			upDir=UpDirektorij(upDir, path, stog);
		
		else if(strcmp(upute, "cd")==0)
			upDir=InDirektorij(upDir, ImeDirektorija, path, stog);

		else if(strcmp(upute, "help")==0)
			Help();
			
		i++;			
	}

return 0;
}


void NoviCvor(Pozicija *P)
{
	Pozicija tmp=NULL;

	tmp=(Pozicija)malloc(sizeof(struct Cvor));

	tmp->isRoot=0;
	tmp->Dijete=NULL;
	tmp->Next=NULL;

	*P=tmp;
}

void NoviStog(Poz *P)
{
	Poz tmp=NULL;

	tmp=(Poz)malloc(sizeof(struct Stog));

	tmp->Next=NULL;
	*P=tmp;
}

void PrintajPath(char *path)
{
	printf("%s>", path);
}

void PrintajDirektorij(Pozicija cvor, char *path)
{
	int i=0;
	printf("\r\nDirektorij od %s", path);

	cvor=cvor->Dijete;

	while(cvor!=NULL)
	{
		printf("\r\n\t<DIR> %s", cvor->ime);
		cvor=cvor->Next;
		i++;
	}

	puts("\r");
	printf("\r\n\t\t %d Dir(s)", i);

	printf("\r\n\r\n");
}

Pozicija UpDirektorij(Pozicija cvor, char *path, Poz S)
{
	int rezultat=0;

	Pozicija tmp=NULL;
	char *a=NULL;

	rezultat=Pop(S, &tmp);

	if(!rezultat)
		return cvor;
	
	a=strrchr(path, '\\');
	if(tmp->isRoot)
		a++;
	
	*a='\0';

	return tmp;

}

void Push(Poz S, Pozicija I)
{
	Poz q = NULL;

	NoviStog(&q);

	q->Cvor = I;

	q->Next = S->Next;
	S->Next = q;
}

int Pop(Poz S, Pozicija *cvor)
{
	Poz tmp = NULL;

	if (NULL == S->Next)
		return 0;

	tmp = S->Next;
	if (tmp == NULL)
		return 0;

	S->Next = tmp->Next;
	if (tmp->Cvor == NULL)
		return 0;

	*cvor = tmp->Cvor;
	free(tmp);

	return 1;
}	

Pozicija InDirektorij(Pozicija cvor, char *ime, char *path, Poz S)
{
	Pozicija tren=NULL;
	char *a=NULL;

	if(cvor==NULL)
		puts("Error");


	tren=cvor->Dijete;

	while(tren !=NULL && _stricmp(tren->ime, ime) !=0)
		tren=tren->Next;
	
	if(tren == NULL)
		{ 
			puts("Error");
			return cvor;
	
		}

	Push(S, cvor);

	if(!cvor->isRoot)
		strcat(path, "\\");

	strcat(path, tren->ime);

	return tren;


}

void StvoriDirektorij(Pozicija cvor, char *ime)
{
	Pozicija q=NULL;

	NoviCvor(&q);

	q->ime=(char *)malloc(sizeof(char)*(strlen(ime)+1));

	memset(q->ime, '\0', (strlen(ime)+1));

	strncpy(q->ime, ime, strlen(ime));

	cvor->Dijete=UmetniDirektorij(q, cvor->Dijete);

}

Pozicija UmetniDirektorij(Pozicija q, Pozicija dijete)
{
	Pozicija prev=NULL;

	if(dijete==NULL) return q;

	if(strcmp(q->ime, dijete->ime)<0)
	{
		q->Next=dijete;
		return q;
	}

	else if(strcmp(q->ime, dijete->ime)==0)
	{
		puts("Direktorij postoji");
		return dijete;
	}

	prev=dijete;

	while(prev->Next!=NULL && strcmp(q->ime, prev->Next->ime)>0)
		prev=prev->Next;

	if(prev->Next !=NULL && strcmp(q->ime, prev->Next->ime)==0)
	{
		puts("Direktorij postoji");
		return dijete;
	}

	q->Next=prev->Next;
	prev->Next=q;

	return dijete;
}

void Help()
{
	printf("\r\n\tdir\t\tDisplays a list of files and subdirectories in a directory.");
	printf("\r\n\tcd\t\tDisplays the name of or changes the current directory.");
	printf("\r\n\tmd\t\tCreates a directory.");
	printf("\r\n\texit\t\tQuits the CMD.EXE program (command interpreter).\n");


}
