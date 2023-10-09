public class Point extends GraphicalObject
{
    public Point(int color, int x, int y) {
        super(color);
        setX(x);
        setY(y);
    }

    public final int getX()
    {
        return x;
    }

    public final void setX(int x)
    {
        this.x = x;
    }

    public final int getY()
    {
        return y;
    }

    public final void setY(int y)
    {
        this.y = y;
    }

    @Override
    public String toString() {
        return super.toString() + "(" + x + ", " + y + ")";
    }

    @Override
    public void draw()
    {
//        System.out.println(this);
        super.draw();
        System.out.print("(" + x + ", " + y + ")");
    }

    private int x;
    private int y;
}
