using System;

namespace CourseProject
{
	class MMV2020
	{

		static byte math(byte math_one, byte math_two)
		{
		byte math_result = 0;
		math_result = (byte)((math_one+standlib.Standlib.Pow(math_one, math_two))%math_two);
		return math_result ;
		}
		static string concat(string concat_a, string concat_b)
		{
		string concat_result = concat_a+concat_b;
		return concat_result ;
		}
		static byte ten()
		{
		return 10 ;
		}
		static void Main(string[] args)
		{
		byte head_l = 4;
		Console.WriteLine(head_l);
		byte head_num = 10;
		Console.WriteLine(head_num);
		bool head_bl = true;
		Console.WriteLine(head_bl);
		byte head_fdfshhvh = 0;
		byte head_c = (byte)(ten());
		Console.WriteLine(head_c);
		byte head_s = 4;
		Console.WriteLine(head_s);
		byte head_f = (byte)(math(head_l, head_s));
		Console.WriteLine(head_f);
		string head_stra = "just ";
		string head_strb = "string";
		string head_strc = concat(head_stra, head_strb);
		Console.WriteLine(head_strc);
		byte head_x = 36;
		byte head_rc = (byte)(standlib.Standlib.MaxNum(head_x, head_s));
		Console.WriteLine(head_rc);
		if (head_rc>head_f)
		{
		Console.WriteLine(head_x);
		}
		else
		{
		Console.WriteLine(head_strc);
		}
		}
		
	}
}