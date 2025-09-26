import java.io.*;
import java.net.*;

public class TCPServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(5000);
        System.out.println("Server started. Waiting for client...");

        Socket socket = serverSocket.accept();
        System.out.println("Client connected.");

        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        while (true) {
            String command = in.readLine();
            if (command == null) break;

            switch (command) {
                case "HELLO":
                    out.println("Hello from Server!");
                    break;

                case "FILE":
                    FileOutputStream fos = new FileOutputStream("received.txt");
                    BufferedInputStream bis = new BufferedInputStream(socket.getInputStream());
                    byte[] buffer = new byte[4096];
                    int bytesRead;
                    while ((bytesRead = bis.read(buffer)) != -1) {
                        fos.write(buffer, 0, bytesRead);
                        if (bytesRead < 4096) break;
                    }
                    fos.close();
                    System.out.println("File received.");
                    break;

                case "CALC":
                    String expression = in.readLine();
                    try {
                        double result = eval(expression);
                        out.println("Result: " + result);
                    } catch (Exception e) {
                        out.println("Error in expression.");
                    }
                    break;

                default:
                    out.println("Unknown command.");
            }
        }

        socket.close();
        serverSocket.close();
    }

    public static double eval(String expr) {
        return new ScriptEngineManager().getEngineByName("JavaScript").eval(expr);
    }
}
