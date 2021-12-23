import java.util.Scanner;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;

public class MemoryCalculator {
	private double currentValue = 0;
	public static int displayMenu() {
		Scanner input = new Scanner(System.in);
		System.out.print("Menu\n1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Clear\n6. Quit\nWhat would you like to do? ");
		int menuChoice = input.nextInt();
		while (menuChoice < 1 || menuChoice > 6) {
			System.out.print("Please enter a valid option.\n\n");
			System.out.print("Menu\n1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Clear\n6. Quit\nWhat would you like to do? ");
			menuChoice = input.nextInt();
		}
		return menuChoice;	
	}
	public static double getOperand(String prompt) {
		Scanner input = new Scanner(System.in);
		System.out.print(prompt);
		double operand = input.nextDouble();
		return operand;
	}
	public double getCurrentValue() {
		return currentValue;
	}
	public void add(double operand2) {
		currentValue = currentValue + operand2;
	}
	public void subtract(double operand2) {
		currentValue = currentValue - operand2;
	}
	public void multiply(double operand2) {
		currentValue = currentValue * operand2;
	}
	public void divide(double operand2) {
		currentValue = currentValue / operand2;
		if (operand2 == 0) {
			currentValue = Double.NaN;
		}
	}
	public EventHandler<ActionEvent> clear() {
		currentValue = 0;
		return null;
	}

}
