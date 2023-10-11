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

    public Abscissa(Abscissa abscissa)
    {
        super(abscissa.getColor());
        Point begin = new Point(abscissa.getColor(), abscissa.getBegin().getX(), abscissa.getBegin().getY());
        // takhle vytvorime kopie toho bodu
        Point end = new Point(abscissa.getColor(), abscissa.getEnd().getX(), abscissa.getEnd().getY());
        setBegin(begin);
        setEnd(end);
        //lokalni kopie bodu, ze kterych pak vyrobime prusecku, normalne by se mel delat u kazde veci kopirovaci konstruktor
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
