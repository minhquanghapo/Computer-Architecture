#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARRAY 1000003

typedef struct data {
	char str[100];
	int count;
} data;

data hashArr[MAX_ARRAY];

void setHashArray()
{
	int i;
	for(i = 0; i < MAX_ARRAY; i++)
		hashArr[i].count = 0;
}

void deleteLetersNotWord(char *str)
{
	int length = strlen(str);
	int i = 0;
	for(i = 0; i < length; i++) {
		if((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z'))
		{
			str[i] = ' ';
		}
		if((str[i] >= 'A' && str[i] <= 'Z'))
		{
			str[i] = str[i] + 32;
		}
	}
}

int powerOf(i, n)
{
	int j;
	if(n == 0) return 1;
	int powi = i;
	for (j = 1; j < n ; j++)
	{
		powi = powi * i;
	}
	return powi;
}

int hashString(char *str)
{
	printf("%s\n", str);
	int length = strlen(str);
	int i;
	int hashNumber, sum = 0;
	for(i = 0; i < length; i++)
	{
		sum += (str[i]) * powerOf(26, i);
	}
	hashNumber = sum % MAX_ARRAY;
	printf("%s: %d \n", str, hashNumber);
	return hashNumber;
}

void insertToHashArray(char *str, int hashNumber)
{
	strcpy(hashArr[hashNumber].str, str);
	hashArr[hashNumber].count ++;
}

void search(char *str)
{
	int hashNumber = hashString(str);
	if(hashArr[hashNumber].count > 0)
	{
		if(!strcmp(str, hashArr[hashNumber].str))
			hashArr[hashNumber].count++;
		else
		{
			while(hashArr[++hashNumber].count != 0);
			insertToHashArray(str, hashNumber);
		}
	}
	else
	{
		insertToHashArray(str, hashNumber);
	}
}


int main()
{
	FILE *fin;
	if((fin = fopen("input.txt", "r")) == NULL) {
		printf("Can't not open file. Try it again!");
	}

	FILE *fptr;
	fptr = fopen("filterInput.txt", "w+");
	char str[100];
	while (fscanf(fin, "%s", str) == 1)
	{
		deleteLetersNotWord(str);
		fprintf(fptr, "%s ", str);
	}
	fclose(fptr);
	fclose(fin);

	if((fin = fopen("filterInput.txt", "r")) == NULL) {
		printf("Can't not open file. Try it again!");
	}

	while (fscanf(fin, "%s", str) == 1)
	{
		search(str);
	}

	int i;
	for(i = 0; i < MAX_ARRAY; i++)
	{
		if(hashArr[i].count > 0)
			printf("%s: %d\n", hashArr[i].str, hashArr[i].count);
	}

	return 0;
}