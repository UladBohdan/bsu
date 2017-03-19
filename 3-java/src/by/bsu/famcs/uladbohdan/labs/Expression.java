package by.bsu.famcs.uladbohdan.labs;

import java.io.*;
import java.util.*;

public class Expression {
	
	private String exprString;
	private StringBuilder revPolish;
	
	public Expression() {
		revPolish = new StringBuilder();
	}
	public Expression(String str) {
		setExpression(str);
		revPolish = new StringBuilder();
	}
	
	public String getExpression() {
		return exprString;
	}
	public void setExpression(String expr) {
		this.exprString = expr;
	}

	public String toReversePolishNotation() throws IOException {
		StringBuilder exprBuilder = new StringBuilder(exprString);
		for (int i=1; i<exprBuilder.length()-1; i++)
			if (exprBuilder.charAt(i-1)=='(' && exprBuilder.charAt(i)=='-' 
				&& exprBuilder.charAt(i+1)>='0' && exprBuilder.charAt(i+1)<='9')
				exprBuilder.setCharAt(i, '$');
		for (int i=0; i<exprBuilder.length()-1; i++)
			if (exprBuilder.charAt(i)!='$' && exprBuilder.charAt(i)!='.' && exprBuilder.charAt(i+1)!='.')
				if (exprBuilder.charAt(i)<'0' || exprBuilder.charAt(i)>'9'
					|| exprBuilder.charAt(i+1)<'0' || exprBuilder.charAt(i+1)>'9') {
					exprBuilder.insert(i+1, '?');
					i++;
				}
		exprBuilder.insert(exprBuilder.length(), '?');
					
		String exprStringTemp = exprBuilder.toString();
		
		StringTokenizer tkn = new StringTokenizer(exprStringTemp,"?");
		
		String cur;
		Stack<String> op = new Stack<String>();
		while (tkn.hasMoreTokens()) {
			cur=tkn.nextToken();
			if (cur.equals("+") || cur.equals("-")) {
				while (!op.isEmpty() && ( op.peek().equals("*") || op.peek().equals("/") || op.peek().equals("^"))) {
					revPolish.append(op.peek());
					revPolish.append(' ');
					op.pop();
				}
				op.push(cur);
			}
			else if (cur.equals("*") || cur.equals("/")) {
				while (!op.empty() && op.peek().equals("^")) {
					revPolish.append(op.peek());
					revPolish.append(' ');
					op.pop();
				}
				op.push(cur);
			}
			else if (cur.equals("^") || cur.equals("("))
				op.push(cur);
			else if (cur.equals(")")) {
				while (!op.isEmpty() && !op.peek().equals("(")) {
					revPolish.append(op.peek());
					revPolish.append(' ');
					op.pop();
				}
				op.pop();
			}
			else { 				// it's a number (or exception)
				int start=0;
				if (cur.charAt(0)=='$')
					start=1;
				for (int i=start; i<cur.length(); i++)
					if ((cur.charAt(i)<'0' || cur.charAt(i)>'9') && cur.charAt(i)!='.')
						throw new IOException("Failed converting "+cur+" to double.");
				if (cur.charAt(0)=='$')
					cur="-"+cur.substring(1);
				revPolish.append(cur);
				revPolish.append(' ');
			}
		}
		
		while (!op.isEmpty()) {
			revPolish.append(op.peek());
			revPolish.append(' ');
			op.pop();
		}
		
		revPolish.deleteCharAt(revPolish.length()-1);
		
		return revPolish.toString();
	}
	
	public double countExpression() throws IOException, NumberFormatException {
		StringTokenizer tkn = new StringTokenizer(revPolish.toString());
		Stack<Double> num = new Stack<Double>();
		while (tkn.hasMoreTokens()) {
			String cur = tkn.nextToken();
			if (cur.charAt(cur.length()-1)>='0' && cur.charAt(cur.length()-1)<='9') {
				num.push(Double.parseDouble(cur));
			}
			else {
				if (num.size()<2)
					throw new IOException("Wrong expression.");
				double val2=num.peek();
				num.pop();
				double val1=num.peek();
				num.pop();
				if (cur.equals("+"))
					num.push(val1+val2);
				else if (cur.equals("-"))
					num.push(val1-val2);
				else if (cur.equals("*"))
					num.push(val1*val2);
				else if (cur.equals("/"))
					num.push(val1/val2);
				else if (cur.equals("^"))
					num.push(Math.pow(val1, val2));
			}
		}
		if (num.size()!=1)
			throw new IOException("Wrong expression.");
		return num.peek();
	}

}

