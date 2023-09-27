package JAVA.lecture2_2;

public class Program 
{    
    public static void main(String[] args)
    {
        Linkedlist list = new Linkedlist();
        list.pushFront(5);
        list.pushFront(3.14);
        list.pushFront("Nazdar");
        list.pushFront(new Numero(10));
        list.myPrint();
    }
}

class Numero
{
    private int numero;
    public Numero(int n)
    {
        numero = n;
    }

    @Override
    public String toString()
    {
        return "" + numero;
    }
}

