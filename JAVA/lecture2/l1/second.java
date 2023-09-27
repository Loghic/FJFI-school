package JAVA.lecture2.l1;

import java.util.Scanner;


public class second
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
        System.out.println("Jeho faktorial je: " + JAVA.lecture2.help.pomoc.factorail(zadano));
        vstup.close();
    }
}

