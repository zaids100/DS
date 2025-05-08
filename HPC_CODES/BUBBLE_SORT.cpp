#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void parallel_bubblesort(vector<int> &arr){
    int n=arr.size(); 
    for(int i=0;i<n;i++){
        int first=i%2;
        #pragma omp parallel for shared(arr,first)
        for(int j=first;j<n-1;j+=2){
            if(arr[j]>arr[j+1]){
               swap(arr[j],arr[j+1]);
            }
        }
     }
}

void bubblesort(vector<int> &arr){
    int n=arr.size(); 
    for(int i=0;i<n;i++){
        // int first=i%2;
        // #pragma omp parallel for shared(arr,first)
        for(int j=0;j<n-1;j++){
            if(arr[j]>arr[j+1]){
               swap(arr[j],arr[j+1]);
            }
        }
     }
}

int main(){
    
    vector<int> arr={10,9,8,7,6,5,4,3,2,1};
    double start=omp_get_wtime();
    parallel_bubblesort(arr);
    double end=omp_get_wtime();
    for(auto e : arr)cout<<e<<"  ";
    cout<<endl;
    cout<<"Execution Time : "<<end-start<<endl;
    return 0;
}