#include "iostream"
#include "vector"
#include "ctime"
#include "omp.h"
#include <bits/stdc++.h>

using namespace std;
// works only for n being of power of 2
extern vector<int> calcPrefixSum(vector<int> input, int num_threads);

vector<int> calcPrefixSum(vector<int> input, int num_threads)
{
    int n = input.size();
    int level = 2;
    while(level<=n)
    {
        int untill = n/level;
        omp_set_num_threads(num_threads);
        #pragma omp parallel for 
        for(int i=0;i<untill;i++)
        {
            int work_for = level*(i+1)-1;
            int get = work_for - (level/2);
            input[work_for] += input[get];
        }
        level *=2;
    }
    int save  = input[n-1];
    input[n-1] = 0;
    while(level!=1)
    {
        int untill = n/level;
        omp_set_num_threads(num_threads);
        #pragma omp parallel for 
        for(int i=0;i<untill;i++)
        {
            int work_for = level*(i+1)-1;
            int get = work_for - (level/2);
            int temp = input[work_for];
            input[work_for] += input[get];
            input[get] =  temp;
        }
        level /= 2;
    }
    input.push_back(save);
    input.erase(input.begin());
    return input;
}



int main(int argc, char *argv[]) {
    int num_threads;
    num_threads = atoi(argv[2]);
    int n;
    n = atoi(argv[1]);
    vector<int> input;
    input.resize(n);
    for (int i = 0; i < n; i++) {
        input[i] = i;
    }

    vector<int> prefixSum;
    double start_time = omp_get_wtime();
    prefixSum = calcPrefixSum(input, num_threads);
    double time_taken = omp_get_wtime() - start_time;

    // Printing stats and results
    cout<< time_taken << endl;
    // cout<< prefixSum.size() << endl;

    for (int i = 0; i < prefixSum.size(); i++){
        // cout << prefixSum[i] << " " ;
    }
    // cout << endl;

    return 0;
}