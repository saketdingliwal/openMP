#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define PADDING 4
int min(int a,int b)
{
	if(a>b)
		return b;
	return a;
}
int a[10000000];
int prefix[20000000];
int
main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
	int NUM_THREADS = atoi(argv[2]);
	int to[2*NUM_THREADS+2][PADDING];
	int p;
	for(int i=0;i<n;i++)
	{
		a[i] = i;
		prefix[i] = 0;
	}
	double start = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
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
	


	int p_save = p;
	int new_p = 1;
	while(p!=0)
	{
		p=p/2;
		new_p *=2;
	}
	p = new_p;
	int level = 2;
	while(level!=p)
	{
		omp_set_num_threads(p/level);
		#pragma omp parallel
		{
			int id = omp_get_thread_num();
			int work_for = level*(id+1)-1;
			int get = work_for - (level/2);
			to[work_for][0] += to[get][0]; 
		}
		level*=2;
	}
	int save  = to[p-1][0];
	to[p-1][0] = 0;
	while(level!=1)
	{
		omp_set_num_threads(p/level);
		#pragma omp parallel
		{
			int id = omp_get_thread_num();
			int work_for = level*(id+1)-1;
			int get = work_for - (level/2);
			int temp = to[work_for][0];
			to[work_for][0] += to[get][0];
			to[get][0] =  temp;
		}
		level /= 2;
	}
	to[p][0] = save;
	p = p_save;


	// for(int i=0;i<p;i++)
	// {
	// 	printf("%d ",to[i+1][0]);
	// }
	// printf("\n");

	omp_set_num_threads(NUM_THREADS);
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
			prefix[i] += to[id][0];
		}		
	}
	double end = omp_get_wtime();
	printf("%lf \n",end - start);

	// for(int i=0;i<n;i++)
	// {
	// 	printf("%d ",a[i]);
	// }
	// printf("\n");
	// for(int i=0;i<n;i++)
	// {
	// 	printf("%d ",prefix[i]);
	// }
	
}