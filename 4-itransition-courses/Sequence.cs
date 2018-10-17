using System;
using System.Collections;

class Sequence {
	static public void Main(string[] args) {
		if (args.Length == 0)
			return;
		string input = args[0];
		if (input == "1")
			return;
		int ones = 0;
		ArrayList ans = new ArrayList ();
		int sh = 0;
		for (int i=0; i<input.Length; i++) {
			char c = input [i];
			if (c < 48 || c > 57) {
				Console.WriteLine ("-");
				return;
			} else if (c == '0') {
				ones += 3;
				ans.Add ("C" + (i+sh));
				sh += 2;
			} else {
				ones += ((int)c - 48);
				sh += ((int)c - 49);
			}
		}
		if (ones % 3 == 0) {
			Console.WriteLine ("-");
			return;
		}
		while ((ones & (ones - 1)) != 0) {
			ans.Add ("D" + ones);
			ans.Add ("C" + ones);
			ans.Add ("A");
			ones += 3;
		}
		while (ones != 1) {
			ans.Add ("B");
			ones /= 2;
		}
		for (int i = ans.Count - 1; i >= 0; i--)
			Console.WriteLine (ans [i]);
	}
}