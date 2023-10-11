
public class Main
{
    private static int maximum(int ... data)
    {
        int res = Integer.MIN_VALUE;

        for (int i : data)
        {
            res = (i > res) ? i : res;
        }
        return res;
    }
    public static void main(String[] args)
    {
        int [] pole = {1,2,5,4,-8,0};
        System.out.println(maximum(pole));
        System.out.println(maximum(8,2,9,1,4,7));
    }
}