using System;

namespace CourseProject
{
	class MMV2020
	{

		static string concat(string concat_a, string concat_b)
		{
		string concat_result = concat_a+concat_b;
		return concat_result ;
		}
		static void Main(string[] args)
		{
		string head_stra = "just ";
		string head_strb = "";
		string head_strc = concat(head_stra, head_strb);
		Console.WriteLine(head_strc);
		}
		
	}
}