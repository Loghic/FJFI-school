namespace linq1
{

  class SkupinaPoDesetiLetich : IEqualityComparer<int>
  {
    public bool Equals(int x, int y)
    {
      return x/10 == y/10;
    }

    public int GetHashCode(int x)
    {
      return (x/10) * 10;
    }
  }

  internal class Program
  {
    private static List<Kontakt> kontakty = new();

    private static void Priprava()
    {
      kontakty.Add(new Kontakt("Jan", "Vopicka", TypKontaktu.Pracovni, "456789", 2000));
      kontakty.Add(new Kontakt("Iva", "Mrazkova", TypKontaktu.Soukromy, "654321", 2005));
      kontakty.Add(new Kontakt("Karel", "Obdrzalek", TypKontaktu.Soukromy, "951753", 2010));
      kontakty.Add(new Kontakt("Alois", "Vostry", TypKontaktu.Pracovni, "123456", 2001));
    }

    private static void VypisSoukromychKontaktu()
    {
      var dotaz = from kontakt in kontakty
                  where kontakt.TypKontaktu == TypKontaktu.Soukromy
                  select kontakt;

      foreach (var kontakt in dotaz)
      {
        Console.WriteLine(kontakt);
      }
    }

    private static void VypisSoukromychKontaktu1()
    {
      IEnumerable<Kontakt> dotaz1 = kontakty.Where(kontakt => kontakt.TypKontaktu == TypKontaktu.Soukromy);
      foreach (var kontakt in dotaz1)
      {
        Console.WriteLine(kontakt);
      }
    }

    private static void KontaktyPodleAbecedy()
    {
      var dotaz = from kontakt in kontakty
                  where kontakt.TypKontaktu == TypKontaktu.Pracovni
                  orderby kontakt.Prijmeni ascending
                  select kontakt.Prijmeni;
      foreach (var kontakt in dotaz)
      {
        Console.WriteLine(kontakt);
      }
    }

    private static void KontaktyPodleAbecedy1()
    {
      var dotaz = kontakty.OrderBy(kontakt => kontakt.Prijmeni).Select(kontakt => kontakt.Prijmeni);

      foreach (var kontakt in dotaz)
      {
        Console.WriteLine(kontakt);
      }
    }

    private static void SkupinyKontaktuPodleTypu()
    {
      var dotaz = from kontakt in kontakty
                  orderby kontakt.Prijmeni
                  group kontakt by kontakt.TypKontaktu;

      foreach (var skupina in dotaz)
      {
        Console.WriteLine("--- " + skupina.Key + " ---");
        foreach (var kontakt in skupina)
        {
          Console.WriteLine(kontakt);
        }
      }

    }

    private static void SkupinyKontaktuPodleTypu1()
    {
      var dotaz = from kontakt in kontakty
                  orderby kontakt.Prijmeni
                  group kontakt.Prijmeni + ": " + kontakt.Telefon by kontakt.TypKontaktu;

      foreach (var skupina in dotaz)
      {
        Console.WriteLine("--- " + skupina.Key + " ---");
        foreach (var kontakt in skupina)
        {
          Console.WriteLine(kontakt);
        }
      }
    }

    private static void SkupinyKontaktuPodleTypu2()
    {
      var dotaz = kontakty
                  .OrderBy(kontakt => kontakt.Prijmeni)
                  .GroupBy(kontakt => kontakt.TypKontaktu, kontakt => kontakt.Prijmeni + ": " + kontakt.Telefon);

      foreach (var skupina in dotaz)
      {
        Console.WriteLine("--- " + skupina.Key + " ---");
        foreach (var kontakt in skupina)
        {
          Console.WriteLine(kontakt);
        }
      }
    }

    private static void VypisPoSkupinach()
    {
      var dotaz = kontakty
                  .GroupBy(kontakt => kontakt.Rok, new SkupinaPoDesetiLetich());

      foreach (var skupina in dotaz)
      {
        Console.WriteLine("--- " + skupina.Key + " ---");
        foreach (var kontakt in skupina)
        {
          Console.WriteLine(kontakt);
        }
      }

    }

    static void Main(string[] args)
    {
      Priprava();
      //VypisSoukromychKontaktu();
      //VypisSoukromychKontaktu1();
      //KontaktyPodleAbecedy();
      //KontaktyPodleAbecedy1();
      //SkupinyKontaktuPodleTypu();
      //SkupinyKontaktuPodleTypu1();
      //SkupinyKontaktuPodleTypu2();
      VypisPoSkupinach();
    }
  }
}
