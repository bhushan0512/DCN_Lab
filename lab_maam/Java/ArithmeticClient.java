package lab_maam.Java;
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class ArithmeticClient {
    public static void main(String[] args) {
        Socket socket = null;
        DataInputStream input = null;
        DataOutputStream output = null;
        Scanner scanner = new Scanner(System.in);

        try {
            socket = new Socket("localhost", 9876);
            System.out.println("Connected to server");

            input = new DataInputStream(socket.getInputStream());
            output = new DataOutputStream(socket.getOutputStream());

            System.out.print("Enter first number: ");
            double number1 = scanner.nextDouble();

            System.out.print("Enter second number: ");
            double number2 = scanner.nextDouble();

            System.out.print("Enter an operator (+, -, *, /): ");
            char operator = scanner.next().charAt(0);

            output.writeDouble(number1);
            output.writeDouble(number2);
            output.writeChar(operator);

            double result = input.readDouble();
            System.out.println("Result: " + result);

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (scanner != null) scanner.close();
                if (input != null) input.close();
                if (output != null) output.close();
                if (socket != null) socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}