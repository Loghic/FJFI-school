namespace delegat
{
  public delegate double Funkce(double x);
  public delegate void Obsluha(double x);

  class Tools
  {
    public event Obsluha obsluha;
  }

  class Priklad
  {
    double x;
    public Priklad(double x)  {this.x = x;}

    public double Soucin(double y)
    {
      Console.WriteLine("Soucin " +  y + " " + x);
      return x * y;
    }
  }

  internal class Program
  {
    static double mocnina(double x)
    {
      // Console.WriteLine("Mocnina " + x);
      return x*x;
    }

    public static void Table(double from, double to, int how_much, Funkce fun)
    {
      double delta = (to - from) / (how_much-1);
      for (int i = 0; i < how_much; ++i)
      {
        double x = from + i * delta;
        Console.WriteLine("{0}   {1}",x, fun(x));
      }

    }

    static void Main(string[] args)
    {
      // Funkce fun = new Funkce(Program.mocnina); // original syntax
      Funkce fun  = mocnina;
      double x = fun(5);
      Console.WriteLine(x);

      Priklad pr = new Priklad(10);

      Funkce fun2 = pr.Soucin;
      double y = fun2(x);
      Console.WriteLine(y);
      // will execute that last added function. It has to be removed with -= to use earlier functions
      fun2 += mocnina;
      y = 1;
      Console.WriteLine(x);
      y = fun2(x);
      Console.WriteLine(y);


      // Table(0, 1, 11, mocnina);
      // Table(0, 1, 11, Math.Sin);

      // Lambda function and how it is possible to write
      Table(0, 1, 11, x => x*x*x);
      // Table(0, 1, 11, (x) => x*x*x);
      // Table(0, 1, 11, (double x) => x*x*x);
      // Table(0, 1, 11, x => {return x*x*x;});
    }
  }
}
