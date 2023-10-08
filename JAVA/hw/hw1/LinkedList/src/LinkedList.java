public class LinkedList {
    public LinkedList()
    {
        head = sentinel = new Element();
    }

    public void pushFront(Object data)
    {
        head = new Element(data, head);
    }

    public void pushBack(Object data)
    {
        sentinel.setData(data);
        sentinel.setNext(new Element(data, null));
        sentinel = sentinel.getNext();
    }

    public void popFirst()
    {
        head = head.getNext(); // ???? idk
    }

    public boolean isEmpty()
    {
        return head == sentinel;
    }

    public void emptyList()
    {
        while(head != sentinel)
        {
            popFirst();
        }
    }

    public void myPrint()
    {
        if (isEmpty())
        {
            System.out.println("Empty list!");
            return;
        }
        Element tmp = head;
        while(tmp != sentinel)
        {
            System.out.print(tmp.getData() + ", ");
            tmp = tmp.getNext();
        }
        System.out.println();
    }

    public Object findSmallest()
    {
        Element smallest = head;
        for (Element tmp = head; tmp != sentinel; tmp = tmp.getNext()){
            if ((int)tmp.getData() < (int)smallest.getData()){
                smallest = tmp;
            }
        }
        return smallest.getData();
    }

    public Object findLargest()
    {
        Element largest = head;
        for (Element tmp = head; tmp != sentinel; tmp = tmp.getNext()){
            if ((int)tmp.getData() > (int)largest.getData()){
                largest = tmp;
            }
        }
        return largest.getData();
    }


    private Element head;
    private Element sentinel;
}
