using System;

namespace standlib
{
    class Program
    {

		static byte math(byte math_one, byte math_two)
		{
			byte math_fr = (byte)(4);
			byte math_wwfgdnvn = (byte)(2);
			byte math_res = (byte)(standlib.Standlib.Pow(math_fr, math_wwfgdnvn));
			Console.Write(math_res);
			string math_lend = "just";
			string math_lenf = " string";
			string math_concat = math_lend + math_lenf;
			Console.Write(math_concat);
			Console.WriteLine();
			byte math_result;
			math_result = (byte)((math_one + standlib.Standlib.Pow(math_fr, math_wwfgdnvn)) * math_two);
			Console.Write(math_result);
			Console.WriteLine();
			return math_result;
		}
		static string value(string value_a)
		{
			return value_a;
		}
		static void Main(string[] args)
		{
			byte head_l = (byte)(14);
			Console.Write(head_l);
			Console.WriteLine();
			byte head_num = (byte)(10);
			Console.Write(head_num);
			Console.WriteLine();
			bool head_bl = true;
			Console.Write(head_bl);
			Console.WriteLine();
			byte head_sdfshhvh;
			byte head_c = (byte)(28);
			string str1 = value("erdfs");
			Console.Write(head_c);
			Console.WriteLine();
			byte head_s = (byte)(75);
			Console.Write(head_s);
			Console.WriteLine();
			byte head_f = (byte)(math(head_c, head_s));
			Console.Write(head_f);
			Console.WriteLine();
			string head_len = "just string";
			string head_lenh = head_len;
			Console.Write(head_len);
			Console.WriteLine();
			byte head_x = (byte)(36);
			byte head_rc = (byte)(standlib.Standlib.MaxNum(head_x, head_s));
			Console.Write(head_rc);
			Console.WriteLine();
			if (head_x < head_f)
			{
				Console.Write(head_len);
			}
			else
			{
				Console.Write(head_s);
			}
		}

	}
}
