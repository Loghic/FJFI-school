namespace binary_numbers
{
  // decimal representation of real numbers
  internal class Program
  {
    static void Main(string[] args)
    {
      double z = -6.6;
      z = Math.Sqrt(z);
      Console.WriteLine("Z is {0}", z);
      decimal delta = 0.1m;
      decimal x = 0m;
      while (x != 1.0m) // For double it would have failed (the condition would never be met => infinite loop)
      {
        Console.WriteLine(x);
        x += delta;
      }
    }
  }
}
