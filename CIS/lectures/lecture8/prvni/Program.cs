using System.Text; // For StringBuilder
namespace prvni
{
  class VypisovacReseni
  {
    private Resitel resitel;
    public int pocetDam {get; private set;}
    public VypisovacReseni(int n)
    {
      pocetDam = n;
      resitel = new(n);
    }

    public void VypisVsechnaReseni()
    {
      while(resitel.NajdiDalsiReseni(out int[] reseni))
      {
        //resitel.Vypis(); // Nefunguje protoze nas Vypis neni thread safe
        StringBuilder text_reseni = new StringBuilder($"{Resitel.PocetReseni}. reseni ulohy {pocetDam} dam: (");
        for (int i =0; i < reseni.Length; i++)
        {
          text_reseni.Append(" " + reseni[i]);
        }
        text_reseni.Append(")");
        Console.WriteLine(text_reseni.ToString());
      }

    }
  }

  internal class Program
  {
    static void Main(string []args)
    {
      var (n1, n2) = (4, 5);
      var vypisovac1 = new VypisovacReseni(n1);
      var vypisovac2 = new VypisovacReseni(n2);
      Thread vlakno1 = new Thread(vypisovac1.VypisVsechnaReseni);
      Thread vlakno2 = new Thread(vypisovac2.VypisVsechnaReseni);
      vlakno1.Start();
      vlakno2.Start();
      vlakno1.Join();
      vlakno2.Join();
      Console.WriteLine("Hotovo");


    }
  }
}
