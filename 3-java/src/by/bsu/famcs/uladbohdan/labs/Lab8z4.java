package by.bsu.famcs.uladbohdan.labs;

public class Lab8z4 {
	
	public static void main(String[] args) {
		try {
			if (args.length==0)
				throw new IllegalArgumentException("Expected an argument");
			System.out.println(args[0]);
			StringBuffer str = new StringBuffer(args[0]);
			for (int i=0; i<str.length(); i++)
				if (str.charAt(i)==' ') {
					str.deleteCharAt(i);
					i--;
				}
			str.append('$');
			int pos=0, c=1;
			while (pos<str.length()-1) {
				while (str.charAt(pos+1)==str.charAt(pos)) {
					c++;
					str.deleteCharAt(pos+1);
				}
				if (c!=1)
					str.insert(pos+1, c);
				c=1;
				pos++;
			}
			str.deleteCharAt(str.length()-1);
			System.out.println(str);
		}
		catch (IllegalArgumentException e) {
			System.out.println(e.getMessage());
		}
		
	}
}
