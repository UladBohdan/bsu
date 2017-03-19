package by.bsu.famcs.uladbohdan.labs;

import java.io.*;

public class Lab8polish {

	public static void main(String[] args) {
		try {
			if (args.length==0)
				throw new IllegalArgumentException("Expression as argument is required.");
			Expression exp = new Expression(args[0]);
			System.out.println("Expression: "+exp.getExpression());
			System.out.println("Reversed polish notation: " + exp.toReversePolishNotation());
			System.out.println("The answer: " + exp.countExpression());
		}
		catch (NumberFormatException e) {
			System.out.println("Double converting error.");
		}
		catch (IOException | IllegalArgumentException e) {
			System.out.println(e.getMessage());
		}
	}

}