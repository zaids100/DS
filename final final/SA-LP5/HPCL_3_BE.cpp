# include <iostream>
# include <omp.h>
# include <sys/time.h>
using namespace std;

int sum_sequential(int arr[], int n)
{
	int sum=0;
	for(int i=0; i<n; i++)
	{
		sum += arr[i];
	}
	return sum;
}
int sum_parallel(int arr[], int n)
{
	int sum=0;
	#pragma omp parallel for reduction(+:sum)
	for(int i=0; i<n; i++)
	{
		sum += arr[i];
	}
	return sum;
}
float avg_sequential(int arr[], int n)
{
	int sum = sum_sequential(arr, n);
	return sum/n;
}
float avg_parallel(int arr[], int n)
{
	int sum = sum_parallel(arr, n);
	return sum/n;
}
int min_sequential(int arr[], int n)
{
	int min=9999999;
	for(int i=0; i<n; i++)
	{
		if(min>arr[i])
			min = arr[i];
	}
	return min;
}
int min_parallel(int arr[], int n)
{
	int min=9999999;
	#pragma omp parallel for reduction(min:min)
	for(int i=0; i<n; i++)
	{
		if(min>arr[i])
			min = arr[i];
	}
	return min;
}
int max_sequential(int arr[], int n)
{
	int max=0;
	for(int i=0; i<n; i++)
	{
		if(max<arr[i])
			max = arr[i];
	}
	return max;
}
int max_parallel(int arr[], int n)
{
	int max=0;
	#pragma omp parallel for reduction(max:max)
	for(int i=0; i<n; i++)
	{
		if(max<arr[i])
			max = arr[i];
	}
	return max;
}
int prod_sequential(int arr[], int n)
{
	int prod=1;
	for(int i=0; i<n; i++)
	{
		prod *= arr[i];
	}
	return prod;
}
int prod_parallel(int arr[], int n)
{
	int prod=1;
	#pragma omp parallel for reduction(*:prod)
	for(int i=0; i<n; i++)
	{
		prod *= arr[i];
	}
	return prod;
}

int main()
{
	int n,ch;
	cout<<"Enter 1-User Defined Array | 2-Static Array : ";
	cin>>ch;
	cout<<"Enter the array length | Any-Custom Array | 100-Static Array : ";
	cin>>n;
	int arr[n];

	if(ch==1)
	{
		for(int i=0; i<n; i++)
		{
			cout<<"Enter element at position "<<i<<" : ";
			cin>>arr[i];
		}
		cout<<endl<<endl;
	}
	else
	{
		int arr2[100] = {52, 93, 15, 72, 61, 21, 83, 87, 75, 75, 88, 24, 3, 22,
		53, 2, 88, 30, 38, 2, 64, 60, 21, 33, 76, 58, 22, 89, 49, 91, 59, 42, 92, 60,
		80, 15, 62, 62, 47, 62, 51, 55, 64, 3, 51, 7, 21, 73, 39, 18, 4, 89, 60, 14, 9,
		90, 53, 2, 84, 92, 60, 71, 44, 8, 47, 35, 78, 81, 36, 50, 4, 2, 6, 54, 4, 54,
		93, 63, 18, 90, 44, 34, 74, 62, 14, 95, 48, 15, 72, 78, 87, 62, 40, 85, 80, 82,
		53, 24, 26, 89};
		for(int i=0; i<n; i++)
			arr[i] = arr2[i];
	}

	cout<<"Array = ";
	for(int i=0; i<n; i++)
		cout<<arr[i]<<",";
	cout<<endl<<endl;

	while(true)
	{
		cout<<"Enter 1-Sum | 2-Avg | 3-Min | 4-Max | 5-Prod | 0-Exit : ";
		cin>>ch;

		struct timeval start, end;

		if(ch==1)
		{ 
			int ans;
			gettimeofday(&start, NULL);
			ans = sum_sequential(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Sum Sequential Answer = "<<ans<<endl;
			cout<<"Sum Sequential Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl;

			gettimeofday(&start, NULL);
			ans = sum_parallel(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Sum Parallel Answer = "<<ans<<endl;
			cout<<"Sum Parallel Reduction Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl<<endl;
		}
		else if(ch==2)
		{ 
			float ans;
			gettimeofday(&start, NULL);
			ans = avg_sequential(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Avg Sequential Answer = "<<ans<<endl;
			cout<<"Avg Sequential Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl;

			gettimeofday(&start, NULL);
			ans = avg_parallel(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Avg Parallel Answer = "<<ans<<endl;
			cout<<"Avg Parallel Reduction Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl<<endl;
		}
		else if(ch==3)
		{ 
			int ans;
			gettimeofday(&start, NULL);
			ans = min_sequential(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Min Sequential Answer = "<<ans<<endl;
			cout<<"Min Sequential Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl;

			gettimeofday(&start, NULL);
			ans = min_parallel(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Min Parallel Answer = "<<ans<<endl;
			cout<<"Min Parallel Reduction Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl<<endl;
		}
		else if(ch==4)
		{ 
			int ans;
			gettimeofday(&start, NULL);
			ans = max_sequential(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Max Sequential Answer = "<<ans<<endl;
			cout<<"Max Sequential Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl;

			gettimeofday(&start, NULL);
			ans = max_parallel(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Max Parallel Answer = "<<ans<<endl;
			cout<<"Max Parallel Reduction Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl<<endl;
		}
		else if(ch==5)
		{ 
			int ans;
			gettimeofday(&start, NULL);
			ans = prod_sequential(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Product Sequential Answer = "<<ans<<endl;
			cout<<"Product Sequential Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl;

			gettimeofday(&start, NULL);
			ans = prod_parallel(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Product Parallel Answer = "<<ans<<endl;
			cout<<"Product Parallel Reduction Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl<<endl;
		}
		else if(ch==0)
		{
			cout<<"Exited Successfully."<<endl;
			break;
		}
		else
		{ 
			cout<<"Invalid Choice."<<endl<<endl;
		}
	}
	return 0;
}