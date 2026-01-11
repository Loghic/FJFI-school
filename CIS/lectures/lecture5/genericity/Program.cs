namespace Genericity
{
  class Point<T>
  {
    T X {get; set; }
    T Y {get; set; }

    public Point(T _X = default, T _Y = default) {this.X = _X; this.Y  = _Y; }

  }

  static class Tools
  {
    public static void vypis<T>(T data)
    {
      Console.WriteLine(data.ToString());
    }

    public static T max<T>(T a, T b) where T : IComparable<T>
    {
      return a.CompareTo(b) > 0 ? a : b;
    }
  }


  class Beta<T> where T : IComparable<T>
  {}



  class X
  {
    public X() {
      Console.WriteLine("Constructor of X");
    }
    public override string ToString()
    {
      return "X";
    }
  }


  internal class Program
  {
    static void Main(string[] args)
    {
      Point<X> b = new Point<X>(new X(), new X());
      Point<int> c = new();
      Tools.vypis(5);
      Tools.vypis(new X());
    }
  }

}

