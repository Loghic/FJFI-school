namespace linq2
{
  internal class Program
  {
    static readonly int[] cisla = {1, 2, 3, 4, 5, 6, 7, 8 };
    static readonly char[] pismena = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    private static int Cislo(char c)
    {
      return c - 'a' + 1;
    }

    static void Main(string[] args)
    {
      var dotaz = from x in pismena
                  from y in cisla
                  where ((y == Cislo(x)) || (y + Cislo(x) == 9))
                  select "(" + x + ", " + y + ") ";

      foreach (var x in dotaz)
      {
        Console.Write(x);
      }
    }
  }
}
