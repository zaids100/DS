import java.util.Scanner;

public class RingAlgorithm {

    public static void main(String[] args) {

        int i, j;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the number of processes: ");
        int numberOfProcesses = scanner.nextInt();

        Process[] processes = new Process[numberOfProcesses];

        // Object initialization
        for (i = 0; i < processes.length; i++)
            processes[i] = new Process();

        // Getting input from users
        for (i = 0; i < numberOfProcesses; i++) {
            processes[i].index = i;
            System.out.println("Enter the ID of process " + (i + 1) + ": ");
            processes[i].id = scanner.nextInt();
            processes[i].state = "active";
            processes[i].hasSentMessage = false;
        }

        // Sorting the processes based on their IDs
        for (i = 0; i < numberOfProcesses - 1; i++) {
            for (j = 0; j < numberOfProcesses - i - 1; j++) {
                if (processes[j].id > processes[j + 1].id) {
                    Process temp = processes[j];
                    processes[j] = processes[j + 1];
                    processes[j + 1] = temp;
                }
            }
        }

        System.out.println("Processes in sorted order:");
        for (i = 0; i < numberOfProcesses; i++) {
            System.out.println("[" + processes[i].index + "] " + processes[i].id);
        }

        // Initiating coordinator selection
        int initiatorIndex;
        while (true) {
            System.out.println("\n1. Initiate Election\n2. Quit");
            int choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    System.out.println("Enter the index of the process initiating the election: ");
                    initiatorIndex = scanner.nextInt();
                    initiateElection(processes, initiatorIndex, numberOfProcesses);
                    break;
                case 2:
                    System.out.println("Program terminated.");
                    return;
                default:
                    System.out.println("Invalid response.");
            }
        }
    }

    public static void initiateElection(Process[] processes, int initiatorIndex, int numberOfProcesses) {
        System.out.println("Election initiated by Process " + processes[initiatorIndex].id);
        processes[initiatorIndex].hasSentMessage = true;

        int tempIndex = initiatorIndex;
        int nextIndex = (initiatorIndex + 1) % numberOfProcesses;
        while (nextIndex != initiatorIndex) {
            if (processes[nextIndex].state.equals("active") && !processes[nextIndex].hasSentMessage) {
                System.out.println("Process " + processes[initiatorIndex].id + " sends message to Process " + processes[nextIndex].id);
                processes[nextIndex].hasSentMessage = true;
                tempIndex = nextIndex;
            }
            nextIndex = (nextIndex + 1) % numberOfProcesses;
        }

        System.out.println("Process " + processes[tempIndex].id + " sends message to Process " + processes[initiatorIndex].id);
        System.out.println("Process " + processes[initiatorIndex].id + " becomes the coordinator.");
        processes[initiatorIndex].state = "inactive";
    }
}

class Process {
    public int index;           // Index of the process
    public int id;              // ID of the process
    public boolean hasSentMessage;  // Flag to indicate whether the process has sent a message
    public String state;        // Indicates whether the process is active or inactive
}
