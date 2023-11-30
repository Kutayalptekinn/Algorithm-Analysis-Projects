#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node{ 
	unsigned long long key;
	char value[40];
	char *relatedWords;
	int tryCount;
}NODE;

NODE* InsertToHash(char word[], int count, NODE *array, int *hashIndex, unsigned long long key);
int IsPrimeNumber(int number);
int CalculateHashTableSize(int count, float loadFactor);
unsigned long long CalculateHashIndex(char word[], int size);

int main(int argc, char *argv[])
{
	char *strt;
	char *strt2;
	char *strt1;	
	NODE *array=NULL;
	int i=0, parity=0, count=0, size, hashIndex=0;
	char searchedWord [80], words [50];
	unsigned long long key;
	float loadFactor=0.75;
	FILE *fp;
	fp = fopen("Sample.txt", "r");
	if (fp==NULL) {
	exit(0);
	}
	while (fgets(words, 50, fp)!=NULL){
	count++;
	}
	fclose(fp);
	count-count/2;
	size=CalculateHashTableSize(count,loadFactor);
    array=(NODE*)calloc(size, sizeof (NODE));
	fp = fopen("Sample.txt", "r");
	if (fp==NULL){
	exit(0);
	}
	while(fgets(words, 50, fp) != NULL)
	{
		if (parity%2==0) {
			key = CalculateHashIndex(words, size);
			hashIndex=key%size;
			array=InsertToHash(words,size,array,&hashIndex,key);
		}
		else{
			array[hashIndex].relatedWords = (char*)malloc(100* sizeof (char));
			strcpy(array[hashIndex].relatedWords, words);
		}
		parity++;
	}

	fclose(fp);
	printf("enter the searched words\n");
	scanf("%[^\n]s", searchedWord);
	
	strt = strtok(searchedWord, " ");
	strt1 = strtok(NULL, " ");
	strt2 = strtok (NULL, " ");
	
	if (strt2==NULL) {
		for (i=0; i<size; i++)
		{
			if(array[i].relatedWords) {
				if(strstr(array[i].relatedWords, strt) != NULL){
					printf("%s try count: %d\n", array[i].value, array[i].tryCount);	
				}
			}
		}
	}
	
	else if(strcmp(strt1,"ve")==0) {
		for (i=0; i<size; i++)
		{
			if(array[i].relatedWords) {
				if(strstr(array[i].relatedWords, strt) != NULL && strstr(array[i].relatedWords,strt2)!=NULL){
				printf("%s try count: %d\n", array[i].value, array[i].tryCount);
				}				
			}
		}
	}
	
	else if(strcmp(strt1,"veya")==0) {
		for (i=0; i<size; i++)
		{
			if(array[i].relatedWords) {
				if(strstr(array[i].relatedWords, strt) != NULL || strstr(array[i].relatedWords,strt2)!=NULL){
				printf("%s try count: %d\n", array[i].value, array[i].tryCount);
				}				
			}
		}
	}
	
	printf("\n \n");
	printf("table elements: \n");
	for (i=0;i<size; i++)
	{
		if (array[i].relatedWords){
			printf("%s try count: %d\n", array[i].value, array[i].tryCount);	
		}
	}
	
	return 0;
	
	
	
}


int IsPrimeNumber(int number)
{
	int i, flag=1;
	for (i= 2; i <= sqrt(number); i++)
	{ 
		if (number % i == 0) {
		flag = 0;
		}
	}
	
	if (number <= 1) {
		flag = 0;
	}
	
	if(flag==1){
		return 1;
	}
	else{
		return 0;
	}
}




unsigned long long CalculateHashIndex(char word[], int size)
{
	int hashIndex, k=31, i, j;	
	int length=strlen(word);
	unsigned long long pow=1, key=0;
	 for (i=0; i<length; i++) {
		for(j=0;j<length-i-1; j++) {
		 	pow=pow*k;
		}
		key+=word[i]*pow;
	}
	return key;
}


int CalculateHashTableSize(int count, float loadFactor)
{
	int flag=1;
	int i=1;
	int reelSize;
	int size=count/loadFactor;
	if (IsPrimeNumber(size)){
		reelSize-size;
	}
	else{
		while(flag){		
			if (IsPrimeNumber(size+i)) {
				reelSize=size+i;
				flag=0;
			}
			else if (IsPrimeNumber(size-i)){
				reelSize=size+i;
				flag=0;
			}
			else{
				flag=1;
				i++;
			}
		}
	}
	return reelSize;
}

NODE* InsertToHash(char word[], int size, NODE *array, int *hashIndex, unsigned long long key)
{
	int i=2;
	while (array[*hashIndex].key && size> (*hashIndex)) {
		(*hashIndex)++;
		array[(*hashIndex)].tryCount=i++;
	}
	if(size>(*hashIndex)){
		array[(*hashIndex)].tryCount=1;
		array[(*hashIndex)].key=key;
		strcpy(array[(*hashIndex)].value, word);
	}
	else{
		printf("full");
	} 
	return array;
}



