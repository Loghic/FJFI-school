namespace LinkedList
{
  class Element<T>
  {
    private T data;
    private Element<T>? next;

    public Element(T _data, Element<T>? _next = null)
    {
      data = _data;
      next = _next;
    }
    public T getData() => data;
    public void setData(T _data) => this.data = _data;
    public Element<T>? getNext() => next;
    public void setNext(Element<T>? _next) => this.next = _next;
  }

  public class List<T>
  {
    private Element<T>? head;
    private uint size = 0;

    public List()
    {
      head = null;
    }

    public void pushFront(T what) {
      head = new Element<T>(what, head);
      ++size;
    }

    public uint getSize() => size;

    public void printList() {
      if (head == null){
        Console.WriteLine("List is empty!");
      } else {
          var tmp = head;
          while(tmp != null){
            Console.Write(tmp.getData() + ", ");
            tmp = tmp.getNext();
        }
        Console.WriteLine();
      }
    }
  }
}

