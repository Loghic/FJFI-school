package l2;

// import java.util.*;
import java.util.Scanner;


public class main
{
    public static void main (String[] args)
    {
        Scanner vstup = new Scanner(System.in);
        System.out.print("Zadej prosim cele cislo: ");
        int zadano = vstup.nextInt();
        System.out.println("Jeho dvojnasobek je: " + zadano*2);
        vstup.close();
    }
}