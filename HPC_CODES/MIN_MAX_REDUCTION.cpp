#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void min_parallel_reduction(vector<int> &arr){
     int mini=INT_MAX;
     #pragma omp parallel for reduction(min : mini)
     for(auto num : arr){
         mini=min(mini,num);
     }
     cout<<"Minimum value after parallel reduction : "<<mini<<endl;
}

void max_parallel_reduction(vector<int> &arr){
    int maxi=INT_MIN;
    #pragma omp parallel for reduction(max : maxi)
    for(auto num : arr){
       maxi=max(maxi,num);
    }
    cout<<"Maximum value after parallel reduction : "<<maxi<<endl;
}

void sum_parallel_reduction(vector<int> &arr){
    int sum=0;
    #pragma omp parallel for reduction(+: sum)
    for(auto num : arr){
       sum+=num;
    }
    cout<<"Summation value after parallel reduction : "<<sum<<endl;
}

void avg_parallel_reduction(vector<int> &arr){
    double sum=0;
    #pragma omp parallel for reduction(+ : sum)
    for(auto num : arr){
        sum+=num;
    }
    cout<<"Average value after parallel reduction : "<<sum/(double)arr.size()<<endl;
}

int main(){
    vector<int> arr={1,2,3,4,5,9};
    double start=omp_get_wtime();
    min_parallel_reduction(arr);
    max_parallel_reduction(arr);
    sum_parallel_reduction(arr);
    avg_parallel_reduction(arr);
    double end=omp_get_wtime();

    cout<<"Total Execution Time : "<<end-start;

}