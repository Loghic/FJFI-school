namespace linq3
{
  internal class Program
  {
    private static readonly Dictionary<int, string> seznamAutoru = new();
    private static readonly Dictionary<int, string> seznamKnih = new();
    private static readonly List<(int cisloAutora, int cisloKnihy)> autorstvi = new();

    static void Main(string[] args)
    {
      seznamAutoru.Add(1, "Karel Capek");
      seznamAutoru.Add(2, "Terry Pratchet");
      seznamKnih.Add(1, "RUR");
      seznamKnih.Add(2, "Muzi ve zbrani");

      autorstvi.Add((1, 1));
      autorstvi.Add((2,2));

      var dotaz = from autor in seznamAutoru
                  join propojeni in autorstvi on autor.Key equals propojeni.cisloAutora
                  join kniha in seznamKnih on propojeni.cisloKnihy equals kniha.Key
                  select autor.Value + ": " + kniha.Value;

      foreach (var kniha in dotaz)
      {
        Console.WriteLine(kniha);
      }
    }

  }
}
