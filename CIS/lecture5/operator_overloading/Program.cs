namespace overloading
{
  internal class Program
  {
    static void Main(string[] args)
    {
      Complex z = new Complex(1, 5);
      Complex w = -z;
      Console.WriteLine(w);
      Complex v = new Complex(1, 2);
      w = z + v;
      Console.WriteLine(w);
      (double x, double y) = w;
      Console.WriteLine(x + " heh " + y);

      v = (5,6);
      Console.WriteLine(v);
      double q = (double)v;

    }
  }
}
