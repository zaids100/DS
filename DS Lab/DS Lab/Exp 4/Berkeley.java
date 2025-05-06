import java.io.*;
import java.net.*;
import java.util.*;

public class Berkeley {

    private static final int PORT = 9876;

    public static void main(String[] args) throws Exception {

        ServerSocket serverSocket = new ServerSocket(PORT);
        List<Long> timeDiffs = Collections.synchronizedList(new ArrayList<Long>());

        Thread timeServerThread = new Thread(() -> {
            while (true) {
                try (Socket clientSocket = serverSocket.accept();
                     ObjectInputStream in = new ObjectInputStream(clientSocket.getInputStream());
                     ObjectOutputStream out = new ObjectOutputStream(clientSocket.getOutputStream())) {

                    Date clientTime = (Date) in.readObject();
                    out.writeObject(new Date());

                    long timeDiff = new Date().getTime() - clientTime.getTime();
                    timeDiffs.add(timeDiff);

                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
        timeServerThread.start();

        Thread timeClientThread = new Thread(() -> {
            while (true) {
                try (Socket socket = new Socket("localhost", PORT);
                     ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
                     ObjectInputStream in = new ObjectInputStream(socket.getInputStream())) {

                    out.writeObject(new Date());
                    Date serverTime = (Date) in.readObject();

                    long timeDiff = serverTime.getTime() - new Date().getTime();
                    timeDiffs.add(timeDiff);

                    Thread.sleep(1000);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
        timeClientThread.start();

        Thread.sleep(20000);

        long sumTimeDiff = 0;
        for (Long timeDiff : timeDiffs) {
            sumTimeDiff += timeDiff;
        }
        long avgTimeDiff = sumTimeDiff / timeDiffs.size();
        System.out.println("Average time difference: " + avgTimeDiff);

        adjustClock(avgTimeDiff);
    }

    private static void adjustClock(long avgTimeDiff) {
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(new Date());
        calendar.add(Calendar.MILLISECOND, (int) avgTimeDiff);
        System.out.println("Adjusted time: " + calendar.getTime());
    }
}