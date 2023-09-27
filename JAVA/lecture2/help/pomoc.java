package JAVA.lecture2.help;

public class pomoc
{
    public static int factorail(int n)
    {
        int vysledek = 1;
        while (n > 1) vysledek *= n--;
        return vysledek;
    }
}