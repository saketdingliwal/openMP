#include <bits/stdc++.h>
#include <omp.h>
#define NUM_THREADS 16
#define PADDING 4

using namespace std;
int min(int a,int b)
{
	if(a>b)
		return b;
	return a;
}

int a[10000000];
int prefix[20000000][PADDING];
int prefix2[20000000];

int
main(int argc, char *argv[])
{

	
	int n = atoi(argv[1]);
	int core_count = atoi(argv[2]);
	
	for(int i=0;i<n;i++)
	{
		int val = i;
		a[i] = val;
		prefix[i][0] = a[i];
	}
	



	double start = omp_get_wtime();
	int n_save = n;
	int new_n = 1;
	while(n!=1)
	{
		n = n/2;
		new_n *= 2;
	}
	if(new_n!=n_save || new_n==1)
		new_n *= 2;

	n = new_n;
	int level = 2;
	while(level<=n)
	{
		int untill = n/level;
		omp_set_num_threads(core_count);
		#pragma omp parallel for 
		for(int i=0;i<untill;i++)
		{
			int work_for = level*(i+1)-1;
			int get = work_for - (level/2);
			prefix[work_for][0] += prefix[get][0];
		}
		level *=2;
	}
	int save  = prefix[n-1][0];
	prefix[n-1][0] = 0;
	while(level!=1)
	{
		int untill = n/level;
		omp_set_num_threads(core_count);
		#pragma omp parallel for 
		for(int i=0;i<untill;i++)
		{
			int work_for = level*(i+1)-1;
			int get = work_for - (level/2);
			int temp = prefix[work_for][0];
			prefix[work_for][0] += prefix[get][0];
			prefix[get][0] =  temp;
		}
		level /= 2;
	}
	prefix[n][0] = save;
	n = n_save;
	
	double end = omp_get_wtime();
	prefix2[0] = a[0];
	for(int i=1;i<n;i++)
	{
		prefix2[i] = prefix2[i-1] + a[i];
	}
	for(int i=0;i<n;i++)
	{
		if(prefix2[i]!=prefix[i+1][0])
			cout << "sdsdsdsdsd";
	}

	cout << (end-start);


	
	for(int i=0;i<=n;i++)
	{
		printf("%d ",prefix[i][0]);
	}
	
}