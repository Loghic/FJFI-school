namespace datatypes
{
  internal class Program
  {
    static (int, int, int) Ntice(int n)
    {
      return (2*n, 4*n*n, n*n*n);
    }

    static int f(int n)
    {
      Console.WriteLine(n);
      return n-1;
    }

    static void Main(string[] args)
    {
      int x = 0;
      int y = 1;
      (x, y) = (5, 6);
      (x, y) = (y, x);
      (string Alpha, string Beta) namedGroup = ("a", "b");

      (int a, double b) xx;
      xx = (5, 3.14);

      Console.WriteLine(xx);

      var (z, u, v) = (1, 3.14, "Whatsup");

      var (_, _, w) = Ntice(5);

      _ = f(5);
    }
  }
}
