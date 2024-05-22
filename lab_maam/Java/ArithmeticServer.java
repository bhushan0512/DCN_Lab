package lab_maam.Java;

import java.io.*;
import java.net.*;

public class ArithmeticServer {
    public static void main(String[] args) {
        ServerSocket serverSocket = null;
        Socket clientSocket = null;

        try {
            serverSocket = new ServerSocket(9876);
            System.out.println("Server is listening on port 9876...");

            while (true) {
                clientSocket = serverSocket.accept();
                System.out.println("Client connected!");

                DataInputStream input = new DataInputStream(clientSocket.getInputStream());
                DataOutputStream output = new DataOutputStream(clientSocket.getOutputStream());

                double number1 = input.readDouble();
                double number2 = input.readDouble();
                char operator = input.readChar();

                double result = performOperation(number1, number2, operator);
                output.writeDouble(result);
                
                System.out.println("Operation performed: " + number1 + " " + operator + " " + number2 + " = " + result);

                input.close();
                output.close();
                clientSocket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (serverSocket != null) serverSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static double performOperation(double number1, double number2, char operator) {
        switch (operator) {
            case '+':
                return number1 + number2;
            case '-':
                return number1 - number2;
            case '*':
                return number1 * number2;
            case '/':
                if (number2 != 0) {
                    return number1 / number2;
                } else {
                    System.out.println("Error: Division by zero");
                    return Double.NaN;
                }
            default:
                System.out.println("Error: Invalid operator");
                return Double.NaN;
        }
    }
}
