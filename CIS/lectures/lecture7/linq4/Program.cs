namespace linq4
{
  class Komparator: IComparer<int>
  {
    public int Compare(int x, int y)
    {
      return Math.Abs(x) - Math.Abs(y);
    }
  }


  internal class Program
  {
    private static int[] pole = {1, -2, 3, -5, -1, -10, 0};

    static void Main(string[] args)
    {
      var pole1 = pole.OrderBy(x => x, new Komparator()).ToArray();
      foreach (var i in pole1)
      {
        Console.Write(i + " ");
      }

    }
  }
}
