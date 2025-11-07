namespace First
{

    public class Tools
    {
      const int BOUNDS = 12;

      public static int Factorial(int n)
      {
        if ((n < 0) || (n > BOUNDS)) {
          throw new ArgumentException("Parameter '" + n + "' is out of bounds");
        }

        int res = 1;
        while (n > 1)
        {
          res *= n--;
        }
        return res;
      }

      public static string? ReadLine() => Console.ReadLine();
      public static int ReadNumber() => Convert.ToInt32(ReadLine());


    }
}
