
public class Main
{
    static int factorial(int n)
    {
        assert n >= 0 : "Negative parameter of factorial!";
        int res = 1;
        while(n > 1) res *= n--;
        return res;
    }
    public static void main(String[] args)
    {
        //add vm eviroment variable and write -ea there
        System.out.println(factorial(-4));
    }
}
