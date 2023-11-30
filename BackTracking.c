#include <stdio.h>
#include <stdlib.h>


void SagaKaydir(int **matris, int satir, int N) {
	int i;
    int temp = matris[satir][N - 1];  

    for (i = N - 1; i > 0; i--) {
        matris[satir][i] = matris[satir][i - 1];
    }

    matris[satir][0] = temp;
}

int BenzerlikKontrol (int **matris, int ilkSatir, int ikinciSatir, int N)
{
	int i, m=1;	
	for (i=0; i<N; i++){
		if (matris[ilkSatir][i]==matris[ikinciSatir][i]){
			return 0;
		}		
	}
	if(ilkSatir>0){
		m=BenzerlikKontrol(matris, ilkSatir-1, ikinciSatir, N);
	}
	return m;
} 

int BackTracking(int **matris, int N){
	int i, count=0;
	for (i=1;i<N; i++){
		count=0;
		while(BenzerlikKontrol(matris, i-1, i, N) == 0){
			SagaKaydir(matris, i, N);
			count++;
			if (count==N){
				return 0;
			}
		}	
	}
	return 1;
}

void printSolution(int **matris, int N, char **renkMatris)
{
	int i, j;	
	for (i=0;i<N; i++) {
		for (j=0; j<N; j++) {
			printf("%s", renkMatris[matris[i][j]-1]);
		}
		printf("\n");
	}
}

int BackTrackingDetay (int **matris, int N, char **renkMatris)
{
	int i, count=0;
	for(i=1;i<N; i++)
	{
		count=0;
		while(BenzerlikKontrol(matris, i-1, i, N) == 0){
			SagaKaydir(matris, i, N);			
			printf("%d. durum: \n", count+1);
			printSolution(matris, N, renkMatris); 
			printf("\n\n");
			count++;
			if(count==N){
				return 0;
			}
		}	
	}
	return 1; 
}


int main()
{
	int N, i, j, choice;
	printf("normal mod icin 1 detay mod icin 2' ye basiniz: \n");
	scanf("%d", &choice);
	printf("n degerini giriniz:\n");
	scanf("%d", &N);
	
	int **matris = (int**)malloc(N * sizeof(int*));
	char **renkMatris = (char**)malloc (N * sizeof(char*));
	
	for (i=0;i<N;i++) {
		matris[i]= (int*)malloc(N * sizeof(int));
		renkMatris[i]=(char*)malloc(10 * sizeof (char));
	}
	
	printf("renklerin numarasi 1'den baslayip artacak sekilde renkleri giriniz: ");
	for (i=0;i<N;i++) {
		printf("\n %d numarali renk: ", i+1);
		scanf("%s", renkMatris[i]);
	}

	printf("Matrisin ilk durumunu giriniz: \n");
	for (i=0; i<N; i++) {
		for (j=0;j<N; j++) {
			printf("matris [%d] [%d]:", i, j);
			scanf("%d", &matris[i][j]);
		}
	}
	
	
	if(choice==1) {
		if(BackTracking(matris, N))
			printSolution(matris, N, renkMatris);	
		else
			printf("Cozum Bulunamadi. \n");
	}
	else if (choice ==2) {
		if(BackTrackingDetay(matris, N, renkMatris))
			printSolution(matris, N, renkMatris);
		else
			printf("Cozum Bulunamadi. \n");	
	}
	else{
		printf("yanlis input");
	}	
}

