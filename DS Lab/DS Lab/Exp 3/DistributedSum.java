import mpi.*;

public class DistributedSum {
    public static void main(String[] args) throws MPIException {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.Rank(); // Rank of current process
        int size = MPI.COMM_WORLD.Size(); // Total number of processes

        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Sample array

        int localSum = 0; // Local sum for each process
        int[] recvBuffer = new int[1]; // Buffer for receiving sum from other processes

        // Distribute elements to different processes
        int startIndex = rank * (array.length / size);
        int endIndex = (rank + 1) * (array.length / size);
        for (int i = startIndex; i < endIndex; i++) {
            localSum += array[i];
        }

        // Print intermediate sums calculated by each process
        System.out.println("Process " + rank + " intermediate sum: " + localSum);

        // Reduce local sums to find global sum
        MPI.COMM_WORLD.Reduce(new int[]{localSum}, 0, recvBuffer, 0, 1, MPI.INT, MPI.SUM, 0);

        // Process 0 prints the final sum
        if (rank == 0) {
            System.out.println("Final sum: " + recvBuffer[0]);
        }

        MPI.Finalize();
    }
}
