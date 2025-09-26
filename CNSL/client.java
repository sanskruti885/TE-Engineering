import java.io.*;
import java.net.*;
import java.util.*;

public class TCPClient {
    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("localhost", 5000);
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
        Scanner sc = new Scanner(System.in);

        System.out.println("Choose option:\n1. Say Hello\n2. Send File\n3. Calculator");
        int choice = sc.nextInt();
        sc.nextLine(); // consume newline

        switch (choice) {
            case 1:
                out.println("HELLO");
                System.out.println("Server says: " + in.readLine());
                break;

            case 2:
                out.println("FILE");
                FileInputStream fis = new FileInputStream("send.txt");
                BufferedOutputStream bos = new BufferedOutputStream(socket.getOutputStream());
                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = fis.read(buffer)) != -1) {
                    bos.write(buffer, 0, bytesRead);
                }
                bos.flush();
                fis.close();
                System.out.println("File sent.");
                break;

            case 3:
                out.println("CALC");
                System.out.print("Enter expression (e.g., 5+3*2): ");
                String expr = sc.nextLine();
                out.println(expr);
                System.out.println("Server response: " + in.readLine());
                break;

            default:
                System.out.println("Invalid choice.");
        }

        socket.close();
    }
}
