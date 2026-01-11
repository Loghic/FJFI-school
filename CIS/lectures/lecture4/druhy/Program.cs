// Deconstruction (makes from variables n-tuple)

namespace Druhy
{
  class Point
  {
    double _x, _y;
    public Point(double x, double y) => (_x, _y) = (x, y);
    public void Deconstruct(out double x, out double y) => (x, y) = (_x, _y);
  }

  internal class Program
  {
    static void Main(string[] args)
    {
      double a, b;
      Point p = new(3, 5);
      (a, b) = p;
      Console.WriteLine((a,b));

    }
  }
}
