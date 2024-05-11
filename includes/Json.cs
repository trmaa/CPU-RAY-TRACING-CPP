using System;
using System.IO;

public class Json{
	public static string read(string src){
		string output = System.IO.File.ReadAllText(src);
		return output;
	}
};
