package l3;

// import java.util.*;
import java.util.Scanner;


public class factorial
{
    public static int factorail(int n)
    {
        int vysledek = 1;
        while (n > 1) vysledek *= n--;
        return vysledek;
    }
    public static void main (String[] args)
    {
        Scanner vstup = new Scanner(System.in);
        System.out.print("Zadej prosim cele cislo: ");
        int zadano = vstup.nextInt();
        System.out.println("Jeho faktorial je: " + Pomoc.factorail(zadano));
        vstup.close();
    }
}

class Pomoc
{
    public static int factorail(int n)
    {
        int vysledek = 1;
        while (n > 1) vysledek *= n--;
        return vysledek;
    }
}