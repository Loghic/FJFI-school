// abscissa is line segment or usecka in czech
public class Abscissa extends GraphicalObject
{
    public final Point getBegin() {
        return begin;
    }

    public final void setBegin(Point begin) {
        this.begin = begin;
    }

    public final Point getEnd() {
        return end;
    }

    public final void setEnd(Point end) {
        this.end = end;
    }

    public Abscissa(int color, Point begin, Point end) {
        super(color);
        setBegin(begin);
        setEnd(end);
    }

    public String toString()
    {
        return super.toString() + "<" + begin + "; " + end + ">";
    }

    @Override
    public void draw()
    {
        super.draw();
        System.out.print("<" + begin + "; " + end + ">");
    }

    private Point begin;
    private Point end;
}
