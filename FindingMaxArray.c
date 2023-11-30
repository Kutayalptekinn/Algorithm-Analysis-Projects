#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int arr[]= {-12, -2, -3, -4, 19, -15, 12, -1, 42, -10, -8};
	int n = sizeof (arr) / sizeof(arr[0]);
	int begin=0;
	int end=n;
	maximum_sum_bruteforce(arr, n);
	printf("The maximum gain with divide and conquer %d\n", maximum_sum_dac(arr, 0, n-1, &begin, &end));
	printf("continuous block %d-->%d", begin, end);
	
	return 0;
}

int maximum_sum_bruteforce (int A[], int n)
{
	int max_sum = INT_MIN;
	int sum = 0, i, j;
	
	for (i = 0; i < n; i++)
	{
		sum = 0;
		
		for(j=i; j < n; j++)
		{
			sum += A[j];
			if (sum > max_sum) {
				max_sum=sum;
			}
		}
	}
	printf("The maximum sum of the subarray with brute force %d\n", max_sum);
}

int maximum_sum_dac (int A[], int low, int high, int *begin, int *end)
{
	if (low == high)
		return A[low];
		
	int mid = (low + high) / 2;
	
	int firstLevel=maximum_sum_dac(A, low, mid, begin, end);
	int secondLevel=maximum_sum_dac(A, mid + 1, high, begin, end);
	
	int sum = 0, i;
	
	int left_sum = INT_MIN;
	
	for (i= mid; i >= low; i--)
	{
		sum = sum + A[i];
		if(sum > left_sum)
		{
			left_sum=sum;
			(*begin)=i;
		}
	}

	sum = 0;
	
	int right_sum = INT_MIN;
	
	
	for (i=mid+1; i <= high; i++) 
	{
		sum=sum+A[i];
	
		if (sum>right_sum)
		{
			right_sum=sum;
			(*end)=i;
		}
	}
	int SumOfRightAndLeft=left_sum+right_sum;
	int max=maxThree(SumOfRightAndLeft, firstLevel, secondLevel);
	
	return max;	
}

int max(int a, int b){ return (a>b) ? a : b;}	

int maxThree(int a, int b, int c) { return max(max(a, b), c); }



