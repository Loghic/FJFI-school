record Point(int x, int y) {}

record Point2(int x, int y)
{
    static int z;
    public static class Inside
    {
        private int N;
        public Inside(int n)
        {
            N = n;
        }

        @Override
        public String toString()
        {
            return "" + N;
        }
    }
    public Point2
    {
        z = 9;
    }

    @Override
    public String toString()
    {
        return x + ", " + y;
//        return x + ", " + y + ", " + z;
    }
}

public class Main
{
    public static void main(String[] args)
    {
//        Point point = new Point(5,4);
        Point2 point = new Point2(5,4);
        System.out.println(point.x());
        System.out.println(point);
        Point2.Inside instance = new Point2.Inside(5);
        System.out.println(instance);
    }
}