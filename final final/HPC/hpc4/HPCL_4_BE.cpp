// HPCL_4_BE_34 - Vector addition, Matrix Multiplication - CUDA C

# include <stdio.h>

__global__ void add_vectors(int *g_a, int *g_b, int *g_c)
{
  int i = threadIdx.x + blockDim.x * blockIdx.x;
  g_c[i] = g_a[i] + g_b[i];
}

void run_vector_addition()
{
    printf("Enter the length of both the vectors : ");    
    int n;
    scanf("%d", &n);
    int c_a[n], c_b[n], c_c[n];
    for (int i=0;i<n;i++) 
    {
        printf("Enter element %d of Vector 1 : ", i);
        scanf("%d", &c_a[i]);
        printf("Enter element %d of Vector 2 : ", i);
        scanf("%d", &c_b[i]);
    }
    
  int *g_a, *g_b, *g_c;
  
    int size = n*sizeof(int);
    cudaMalloc(&g_a, size);
    cudaMalloc(&g_b, size);
    cudaMalloc(&g_c, size);
    cudaMemcpy(g_a, c_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(g_b, c_b, size, cudaMemcpyHostToDevice);
    cudaMemcpy(g_c, c_c, size, cudaMemcpyHostToDevice);
  
    add_vectors<<<1,n>>>(g_a, g_b, g_c); // n Blocks * 1 Thread = n Threads in total.
    cudaDeviceSynchronize();
    cudaMemcpy(c_c, g_c, size, cudaMemcpyDeviceToHost);
  
    cudaFree(g_a);
    cudaFree(g_b);
    cudaFree(g_c);

    printf(" ");
    for (int i=0;i<n;i++) 
        printf("%d ", c_a[i]);
    printf("\n+");
    for (int i=0;i<n;i++) 
        printf("%d ", c_b[i]);
    printf("\n=");
    for (int i=0;i<n;i++) 
        printf("%d ", c_c[i]);
    printf("\n");
}

__global__ void matrix_multiply(int *g_a, int *g_b, int *g_c, int size)
{
  int idx = blockDim.x * blockIdx.x + threadIdx.x;
  for(int i=0; i<size; i++)
      g_c[idx] += g_a[blockDim.x * blockIdx.x + i] * g_b[i * blockDim.x + threadIdx.x];
}

void run_matrix_multiplication()
{
    int n=3;    
    int c_c[3][3] = {{0,0,0},
                     {0,0,0},
                     {0,0,0}};
  
    int c_a[n][n], c_b[n][n];
    for (int i=0;i<n;i++) 
    {
        for (int j=0;j<n;j++) 
        {
            printf("Enter element %d,%d of Matrix A : ", i, j);
            scanf("%d", &c_a[i][j]);
            printf("Enter element %d,%d of Matrix B : ", i, j);
            scanf("%d", &c_b[i][j]);
        }
    }

  int *g_a, *g_b, *g_c;
  
  int size = n*n*sizeof(int);
  cudaMalloc(&g_a, size);
  cudaMalloc(&g_b, size);
  cudaMalloc(&g_c, size);
  cudaMemcpy(g_a, c_a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(g_b, c_b, size, cudaMemcpyHostToDevice);
  cudaMemcpy(g_c, c_c, size, cudaMemcpyHostToDevice);
  
  matrix_multiply<<<n,n>>>(g_a, g_b, g_c, size); // 3 Blocks, each having 3 threads
  cudaDeviceSynchronize();
  cudaMemcpy(c_c, g_c, size, cudaMemcpyDeviceToHost);
  
  cudaFree(g_a);
  cudaFree(g_b);
  cudaFree(g_c);

    printf("A = \n");
    for (int i=0;i<n;i++) 
    {
        for (int j=0;j<n;j++) 
            printf("%d,", c_a[i][j]);
        printf("\n\n");
    }
    printf("B = \n");
    for (int i=0;i<n;i++) 
    {
        for (int j=0;j<n;j++) 
            printf("%d,", c_b[i][j]);
        printf("\n\n");
    }
    printf("Multiplication = \n");
    for (int i=0;i<n;i++) 
    {
        for (int j=0;j<n;j++) 
            printf("%d,", c_c[i][j]);
        printf("\n\n");
    }
}

int main() 
{
    int ch;
    while(true)
    {
        printf("Enter 1-Vector Addition | 2-Matrix Multiplication | 0-Exit : ");
        scanf("%d", &ch);
        if(ch==1)
            run_vector_addition();
        else if(ch==2)
            run_matrix_multiplication();
        else if(ch==0)
        {
            printf("Exited Successfully.\n");
            break;
        }
        else
            printf("Invalid input.\n");
    }

    return 0;
}
