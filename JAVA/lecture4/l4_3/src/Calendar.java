public class Calendar
{
    public Calendar(int day, int month, int year)
    {
        setDay(day);
        setMonth(month);
        setYear(year);
    }
    public static boolean leapYear(int year)
    {
        return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    }

    int numberOfDay()
    {
        var res = numOfDaysTillBeginOfMonth[month] + day;
        if(leapYear(year) && month  > 2) res++;
        return res;
    }
    public int getDay()
    {
        return day;
    }
    public final void setDay(int day)
    {
        this.day = day;
    }

    public int getMonth()
    {
        return month;
    }

    public final void setMonth(int month)
    {
        this.month = month;
    }

    public int getYear()
    {
        return year;
    }

    public final void setYear(int year)
    {
        this.year = year;
    }

    private int day,month, year;
    private static final int[] DAYS_IN_MONTH = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    private static int numOfDaysTillBeginOfMonth []= new int [13];

    static
    {
        numOfDaysTillBeginOfMonth[0] = 0;
        numOfDaysTillBeginOfMonth[1] = 0;
        for (int actual = 2; actual <= 12; actual++)
        {
            int prev = actual-1;
            numOfDaysTillBeginOfMonth[actual] = numOfDaysTillBeginOfMonth[prev] + DAYS_IN_MONTH[prev];
        }

    }
}
