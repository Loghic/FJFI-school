namespace Arrays
{
  internal class Calendar
  {
    private static int[] days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    private int[] count_of_days_till_start = new int[12];
    public Calendar()
    {
      count_of_days_till_start[0] = 0;
      for (int i = 1; i < 12; ++i)
      {
        count_of_days_till_start[i] = count_of_days_till_start[i - 1] + days_in_month[i - 1];
      }
    }

    public static bool is_leap_year(int year)
    {
      return ((year % 400 == 0) || (year % 4 == 0) && (year % 100 != 0));
    }

    public int NumberOfDay(int day, int month, int year)
    {
      int res = count_of_days_till_start[month-1] + day;
      if(is_leap_year(year) && (month > 1))
      {
        ++res;
      }
      return res;
    }

    public void Vypis() // For debuging
    {
      foreach (int i in count_of_days_till_start)
      {
        Console.Write("{0} ", i);
      }
    }
  }
}
