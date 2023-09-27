package JAVA.lecture2_2;

public class Prvek 
{
    public Prvek(Object data, Prvek next)
    {
        setData(data);
        setNext(next);
    }

    public Prvek()
    {
        this.data = null;
        this.next = null;
    }

    public final Object getData()
    {
        return data;
    }

    public final void setData(Object data)
    {
        this.data = data;
    }

    public final Prvek getNext()
    {
        return next;
    }

    public final void setNext(Prvek next)
    {
        this.next = next;
    }

    private Prvek next;
    private Object data;
}
