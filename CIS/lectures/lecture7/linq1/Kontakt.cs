namespace linq1
{
  public enum TypKontaktu {Soukromy, Pracovni}

  public class Kontakt
  {
    public string Jmeno { get; set; }

    public string Prijmeni { get; set; }

    public TypKontaktu TypKontaktu { get; set; }

    public string Telefon { get; set;}

    public int Rok { get; set; }

    public Kontakt(string jmeno, string prijmeni, TypKontaktu typKontaktu, string telefon, int rok)
    {
      (Jmeno, Prijmeni, TypKontaktu, Telefon, Rok) = (jmeno, prijmeni, typKontaktu, telefon, rok);
    }

    public override string ToString()
    {
      return Jmeno + " " + Prijmeni + " (typ: " + TypKontaktu + " telefon: " + Telefon + ", " + Rok + ")";
    }

  }
}

