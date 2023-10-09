
class answer
{
    private int value;
    public answer(int value)
    {
        this.value = value;
    }
    public answer()
    {
        this(Tools.ANSWER);
    }
    @Override
    public String toString()
    {
        return "" + value;
    }

}

class Tools
{
    // static makes things useable outside of class (parents and childs)
    public static final int ANSWER = 42; // this is constant
    //array of ints or specific ints and compiler makes array from them
    public static int maximum(int ... data)
    {
        int res = Integer.MIN_VALUE;
        for (int i: data)
        {
            if (i > res)
            {
                res = i;
            }
        }
        return res;
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println(new answer());
        int[] array = {4,5,10,2,8};
        System.out.println(Tools.maximum(array));
        System.out.println(Tools.maximum(20,31,5,87,99,4,-7));

    }
}