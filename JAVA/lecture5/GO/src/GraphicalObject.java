public abstract class GraphicalObject
{

    public GraphicalObject(int color)
    {
        setColor(color);
    }

    public GraphicalObject(GraphicalObject go)
    {
        setColor(go.getColor());
    }

    public GraphicalObject()
    {
        this(0);
    }

    public final int getColor() {
        return color;
    }

    public final void setColor(int color) {
        this.color = color;
    }

    @Override
    public String toString()
    {
        return "[" + getColor() + "]";
    }

    public abstract GraphicalObject kopie();

    public void draw()
    {
//        System.out.println(this);
        System.out.print("[" + getColor() + "]");
    }

    private int color;
}
