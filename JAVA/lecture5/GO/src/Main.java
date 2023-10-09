public class Main
{
    public static void main(String[] args)
    {
//        GraphicalObject go = new Point(5,6,7);
        GraphicalObject go = new Abscissa(55, new Point(5,2,1),
                new Point(4,8,9));
        go.draw();
    }
}