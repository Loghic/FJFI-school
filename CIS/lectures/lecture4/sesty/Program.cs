namespace Sesty
{
  public struct Complex
  {
    private double X {get; set;}
    private double Y {get; set;}

    public Complex(double x, double y)
    {
      X = x;
      Y = y;
    }
    public Complex Plus(Complex z)
    {
      return new Complex(X + z.X, Y + z.Y);
    }

    public override string ToString()
    {
        return "(" + X + ", " + Y +"j)";
    }
  }

  public readonly struct Complex1
  {
    private readonly double x;
    private readonly double y;

    public double X => x;
    public double Y => y;

    public Complex1(double x, double y)
    {
      this.x = x;
      this.y = y;
    }
  }

  internal class Program
  {
    static void Main(string [] args)
    {
      Complex c1 = new Complex(3, 5);
      Complex c2 = new Complex(-3, 10);
      Complex c = c1.Plus(c2);
      Console.WriteLine(c);
      // Object obj = c; // "Encapsulation"
    }
  }
}
