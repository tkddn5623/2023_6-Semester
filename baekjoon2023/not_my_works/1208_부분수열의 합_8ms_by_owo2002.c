#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#define size 4000000
int arr[41];
int ar[2*size+1];
long long int cnt;
int n, s;

int cmp(const void* a, const void* b)
{
	if (*(int*)a > *(int*)b)
		return 1;
	else
		return -1;
}

void left(int idx, int sum)
{
	if (idx == n/2)
	{
		ar[size + sum]++;
		return;
	}
	left(idx + 1, sum + arr[idx]);
	left(idx + 1, sum);
}

void right(int idx, int sum)
{
	if (idx == n)
	{
		cnt += ar[size +s - sum];
		return;
	}
	right(idx + 1, sum + arr[idx]);
	right(idx + 1, sum);
}

int main()
{
	scanf("%d %d", &n, &s);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	qsort(arr, n, 4, cmp);

	left(0, 0);
	right(n/2, 0);

	if(s==0)
		printf("%lld", cnt-1);
	else
		printf("%lld", cnt);
}