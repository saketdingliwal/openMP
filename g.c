#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define NUM_THREADS 10
#define PADDING 4
int min(int a,int b)
{
	if(a>b)
		return b;
	return a;
}

int
main(int argc, char *argv[])
{
	omp_set_num_threads(NUM_THREADS);
	int n = 10000;
	int a[n];
	int prefix[n];
	int to[NUM_THREADS][PADDING];
	int p;
	for(int i=0;i<n;i++)
	{
		a[i] = i;
		prefix[i] = 0;
	}
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		p = omp_get_num_threads();
		int block_size = n/p;
		if(n%p!=0)
			block_size = block_size + 1;
		int start = min(id*block_size,n);
		int end = min((id+1)*block_size,n);
		for(int i=start;i<end;i++)
		{
			if(i!=start)
				prefix[i] += prefix[i-1] + a[i];
			else
				prefix[i] = a[i];
		}
		to[id][0] = prefix[end-1];			
	}
	// for(int i=0;i<p;i++)
	// {
	// 	printf("%d ",to[i][0]);
	// }
	// printf("\n");
	int level = 2;
	while((level/2) < p)
	{
		#pragma omp parallel
		{
			int id = omp_get_thread_num();
			int position = id%level - (level/2)  + 1;
			if(position>0)
			{
				to[id][0] += to[id-position][0];
			}
		}
		level*=2;
	}
	// for(int i=0;i<p;i++)
	// {
	// 	printf("%d ",to[i][0]);
	// }
	// printf("\n");
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		p = omp_get_num_threads();
		int block_size = n/p;
		if(n%p!=0)
			block_size = block_size + 1;
		int start = min(id*block_size,n);
		int end = min((id+1)*block_size,n);
		for(int i=start;i<end;i++)
		{
			if(id!=0)
				prefix[i] += to[id-1][0];
		}		
	}
	// for(int i=0;i<100;i++)
	// {
	// 	printf("%d ",a[i]);
	// }
	// printf("\n");
	// for(int i=0;i<100;i++)
	// {
	// 	printf("%d ",prefix[i]);
	// }
	
}