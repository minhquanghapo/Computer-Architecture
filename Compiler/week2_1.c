#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxZero = 0;
const prime = 1000003;
unsigned long hash(char *str)
    {
        unsigned long hash = 5381;
        int c;
        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }
void maxLengthZero(unsigned long hashNumber)
{
	 int num = 0;
	 while(hashNumber != 0)  
    {  
        if(hashNumber % 2 == 1) break;
        num++;
        hashNumber = hashNumber/2;
    }
    if(num > maxZero)
   	maxZero = num;
} 


int main()
{
	char str[100];
	FILE *fin;
	if((fin = fopen("input.txt", "r")) == NULL) {
		printf("Can't not open file. Try it again!");
	}
	while (fscanf(fin, "%s", str) == 1)
	{
		maxLengthZero(hash(str));
	}
	printf("%d\n", maxZero);
	printf("Number of words difference is: %d", 1 << maxZero);
	return 1;
}