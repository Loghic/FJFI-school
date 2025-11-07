namespace Prvni
{
  internal class Program
  {
    static int Factorial(int n)
    {
      int result = 1;
      while(n>1) result *= n--;
      return result;
    }

    // paramaters passed as a reference
    static void Swap_vars(ref int a, ref int b)
    {
      (a, b) = (b, a);
    }

    // the parameter does not have to be initialized, but in the body we have to assing some value to it
    static void Initialize_var(out int n)
    {
      n = 42;
    }

    // Method with variable number of parameters
    static int Max(params int[]data)
    {
      if ((data == null) || data.Length == 0) return Int32.MinValue;

      int result = Int32.MinValue;
      foreach(int i in data)
      {
        if (i > result) result = i;
      }


      return result;
    }

    static void Main(string[] args)
    {
      int n = 5;
      Console.WriteLine(Factorial(n));
      Console.WriteLine(n);
      int a = 10;
      int b = 15;
      Swap_vars(ref a, ref b);
      Console.WriteLine(a + " " + b);
      int c;
      // Swap_vars(c, a); Not possible - variable 'c' has to be initialized
      Initialize_var(out c);
      Console.WriteLine(Max());
      Console.WriteLine(Max(a,b,c,n));
      int[] M = {5,4,-7,2,11,0};
      Console.WriteLine(Max(M));
    }
  }
}

