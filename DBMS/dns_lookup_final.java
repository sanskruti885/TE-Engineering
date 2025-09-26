

import java.net.*;
import java.util.*;

public class dns_lookup_final{
    public static void main(String args[]){
        String host;
        Scanner sc = new Scanner(System.in);
        System.out.println("1.Enter Host Name\n2. Enter IP Address\nChoice: ");
        int choice = sc.nextInt();

        if(choice == 1){
            Scanner input = new Scanner(System.in);
            System.out.println("\nEnter host name");
            host = input.nextLine();
            try{
                InetAddress address = InetAddress.getByName(host); //resolve the hostname into an IP address.
                System.out.println("IP Address: "+address.getHostAddress());
                System.out.println("Host Name: "+address.getHostName());
                System.out.println("Host name and IP address: "+address.toString());
            }
            catch(UnknownHostException ex){
                System.out.println("Could not find "+host);
            }
        }
        else if (choice == 2){
            Scanner input = new Scanner(System.in);
            System.out.println("\nEnter the IP address: ");
            host = input.nextLine();

            try{
                InetAddress address = InetAddress.getByName(host);
                System.out.println("Host Name: "+address.getHostName());
                System.out.println("IP Address: "+address.getHostAddress());
                System.out.println("Host name and IP address: "+address.toString());
            }
            catch(UnknownHostException ex){
                System.out.println("Could not find "+host);
            }
        }
        else{
            System.out.println("\nWrong choice.");
        }
    }
}