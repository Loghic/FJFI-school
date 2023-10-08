public class Element {
    public Element (Object data, Element next)
    {
        setData(data);
        setNext(next);
    }
    public Element ()
    {
        data = null;
        next = null;
    }

    public final void setData(Object data)
    {
        this.data = data;
    }

    public final Object getData()
    {
        return data;
    }

    public final void setNext(Element next)
    {
        this.next = next;
    }

    public final Element getNext()
    {
        return next;
    }


    private Object data;
    private Element next;
}
