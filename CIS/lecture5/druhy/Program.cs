namespace Interface2
{
  public interface IKontrola
  {
    bool Zkontroluj();
    const int N = 123;
    void Pozdrav()
    {
      Console.WriteLine("Nazdar!");
    }
  }

  public interface ISavable
  {
    bool Zkontroluj();
    void Save();

    static int Odpoved()
    {
      return 42;
    }
  }

  class Alfa : IKontrola, ISavable
  {
      bool IKontrola.Zkontroluj()
      {
        Console.WriteLine("Zkontrolovano!");
        return true;
      }

      bool ISavable.Zkontroluj()
      {
        Console.WriteLine("Zkontrolovano, lze ulozit!");
        return true;
      }

      public bool Zkontroluj()
      {
        Console.WriteLine("Kontrola jentak!");
        return true;
      }

      void ISavable.Save()
      {
        Console.WriteLine("Saved!");
      }

      public void Pozdraveni()
      {
        ((IKontrola)this).Pozdrav();
      }
    }

  internal class Program
  {
    static void Kontrola(IKontrola kontrola)
    {
      kontrola.Zkontroluj();
    }

    static void Saving(ISavable savable)
    {
      savable.Zkontroluj();
      savable.Save();
    }

    static void Main(string[] args)
    {
      Alfa alfa = new Alfa();
      Kontrola(alfa);
      Saving(alfa);
      ((IKontrola)alfa).Zkontroluj();
      alfa.Zkontroluj();

      int i = IKontrola.N;

      ((IKontrola)alfa).Pozdrav();

      alfa.Pozdraveni();

      Console.WriteLine(ISavable.Odpoved());

    }
  }
}
