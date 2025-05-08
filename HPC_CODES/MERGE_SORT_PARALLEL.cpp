#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
#define ll long long

void merge(vector<int> &arr,int ls,int le,int rs,int re){
     vector<int> temp;
     int i=ls;
     int j=rs;
     while(i<=le && j<=re){
         if(arr[i]<=arr[j]){
            temp.push_back(arr[i++]);
         }else{
            temp.push_back(arr[j++]);
         }
     }
     while(i<=le){
         temp.push_back(arr[i++]);
     }
     while(j<=re){
        temp.push_back(arr[j++]);
     }
     for(int k=0;k<temp.size();k++){
         arr[ls+k]=temp[k];
     }

}

void parallelMergeSort(vector<int>& arr, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, start, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, end);
            }
        }
        merge(arr, start, mid, mid + 1, end);
    }
}

int main()
{       
    vector<int> arr={10,9,8,7,6,5,-1,-2,-100};
    double startTime=omp_get_wtime();
    parallelMergeSort(arr,0,arr.size()-1);
    double endTime=omp_get_wtime();

    for(auto num : arr){
        cout<<num<<"  ";
    }

    cout<<endl<<"Total Execution Time : "<<endTime-startTime;

    return 0;
}