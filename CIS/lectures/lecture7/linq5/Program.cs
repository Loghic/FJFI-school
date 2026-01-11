namespace linq5
{
  internal class Program
  {
    static int Faktorial(int n)
    {
      return Enumerable.Range(1, n).Aggregate(1, (seme, x) => seme * x);
    }

    private static void PythagorejskeTrojice(int n)
    {
      var vsechnyTrojice = from a in Enumerable.Range(1, n)
                           from b in Enumerable.Range(1, n)
                           from c in Enumerable.Range(1, n)
                           where (a <= b) && (a*a + b*b == c*c)
                           select (prvni: a, druha: b, treti: c);

      foreach (var (prvni, druha, treti) in vsechnyTrojice)
      {
        Console.WriteLine("" + prvni + ", " + druha + ", " + treti);
      }
    }

    static void Main(string[] args)
    {

      Console.WriteLine(Faktorial(5));
      PythagorejskeTrojice(20);

    }
  }
}
