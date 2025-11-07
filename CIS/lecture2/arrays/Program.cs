namespace Arrays
{
  internal class Program
  {
    static void Main(string[] args)
    {
      Calendar calendar = new();
      calendar.Vypis();
      Console.WriteLine(Calendar.is_leap_year(1900));
      Console.WriteLine(calendar.NumberOfDay(5, 1, 2025));
      Console.WriteLine(calendar.NumberOfDay(5, 2, 2025));
      Console.WriteLine(calendar.NumberOfDay(1, 3, 2025));
      Console.WriteLine(calendar.NumberOfDay(1, 3, 2024));

      int[,] a = new int[,] { {1, 2, 3, }, { 4, 5, 6,} };

    }
  }
}
