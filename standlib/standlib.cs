using System;
using System.Collections.Generic;
using System.Text;

namespace standlib
{
    public static class Standlib
    {
        static public int Pow(int num, int deg)
        {
            if (deg < 0)
            {
                Console.WriteLine("Cannot raise to a negative degree ");
                return 0;
            }
            int result = 1;
            while (deg != 0)
            {
                if (deg % 2 == 0)
                {
                    deg /= 2;
                    num *= num;
                }
                else
                {
                    deg--;
                    result *= num;
                }
            }
            return result;
        }
        static public int MaxNum(int num1, int num2)
        {
            if (num1 > num2)
            {
                return num1;
            }
            return num2;
        }
    }
}
