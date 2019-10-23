#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct {

	char ime[50];
	char prezime[50];
	int bodovi;

}studenti;

int countstd(char* a)
{
	int n = 0;
	char s[50];
	FILE* fp = NULL;

	fp = fopen(a, "r");

	while (!feof(fp)) {
		if (fgets(s, 50, fp))
			n++;
	}
	fclose(fp);

	return n;
}

void readstd(char* a, studenti* ptr, int n) {

	int i = 0;
	FILE* fp = NULL;

	fp = fopen(a, "r");

	for (i = 0; i < n; i++)
	{

		fscanf(fp, "%s %s %d", ptr[i].ime, ptr[i].prezime, &ptr[i].bodovi);


	}

	fclose(fp);

}

int Max(int n, studenti* ptr) {
	int max = 0;
	int i = 0;

	max = ptr[0].bodovi;

	for (i = 0; i < n; i++) {

		if (ptr[i].bodovi > max)
			max = ptr[i].bodovi;

	}

	return max;
}

void print(studenti* ptr, int n, int max) {

	int i = 0;

	for (i = 0; i < n; i++)
	{

		printf("%s %s %d r=%.2f posto\n", ptr[i].ime, ptr[i].prezime, ptr[i].bodovi, ptr[i].bodovi / (float)max * 100);


	}

}

int main()
{
	int n = 0, i=0;
	int max = 0;
	studenti* ptr = NULL;

	n = countstd("Studenti.txt");

	printf("broj studenata je : %d\n", n);

	ptr = (studenti*)malloc(n * sizeof(studenti));

	readstd("Studenti.txt", ptr, n);

	max = Max(n, ptr);


	printf("max je %d\n", max);

	print(ptr, n, max);

	getchar();

	return 0;
}