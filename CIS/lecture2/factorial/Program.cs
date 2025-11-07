namespace factorial
{
  // Check of int arithmethic overflow
  internal class Program
  {
    // Can overflow
    public static int Factorial0(int n) // Without check
    {
      int res = 1;
      while (n > 1)
      {
        res *= n--;
      }

      return res;
    }

    public static int Factorial1(int n) // With check
    {
      int res = 1;
      while (n > 1)
      {
        // operator checked
        res = checked(res * n--);
      }

      return res;
    }

    public static int Factorial2(int n) // With check, different possibility
    {
      int m = n;
      int res = 1;
      try
      {
        checked // Block checked
        {
          while (m > 1)
          {
            res = checked(res * m--);
          }
        }

      }
      catch (OverflowException e)
      {
        res = 0;
        Console.WriteLine("Arithmethic overflow for n = {0}", n);
      }

      return res;
    }

    static void Main(string[] args)
    {
      try
      {
        for (int i = 0; i < 15; ++i)
        {
          Console.WriteLine("Factorial {0} is {1}", i, Factorial2(i));
        }
      } catch (System.OverflowException e) {
          Console.WriteLine(e.Message);
      }
    }
  }
}
