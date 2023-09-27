package JAVA.lecture2_2;

public class Linkedlist 
{
    public Linkedlist()
    {
        head = tail = new Prvek();
    }
    public void pushFront(Object data)
    {
        head = new Prvek(data, head);
    }

    public boolean empty()
    {
        return head == tail;
    }

    public void myPrint()
    {
        if (empty())
        {
            System.out.println("Empty list!");
            return;
        }
        Prvek tmp = head;
        while(tmp != tail)
        {
            System.out.print(tmp.getData() + ", ");
            tmp = tmp.getNext();
        }

    }

    private Prvek head;
    private Prvek tail;
}
