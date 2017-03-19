package by.bsu.famcs.uladbohdan.labs;

public class Lab7 {
	public static void main(String[] args) {
		try {
			if (args.length!=2)
				throw new IllegalArgumentException("Not 2 arguments!");
			double x=Double.parseDouble(args[0]);
			double e=Double.parseDouble(args[1]);
			if (Math.abs(x)>1)
				throw new IllegalArgumentException("Bad x value.");
			System.out.println("Sum="+sum(x,e));
		}
		catch (NumberFormatException e) {
			System.out.println("Converting failed: "+e.getMessage());
		}
		catch (IllegalArgumentException e) {
			System.out.println(e.getMessage());
		}
	}
	
	private static double sum(double x, double e) {
		double a=x*(-2)/3;
		double ans=a;
		double k=2;
		while (Math.abs(a)>e) {
			a=a*(-x/3)*(k+1)/k;
			ans+=a;
			k++;
		}
		return ans;
	}

}