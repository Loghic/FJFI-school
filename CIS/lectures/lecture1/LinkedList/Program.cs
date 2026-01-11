namespace LinkedList
{
  internal class Word
  {
    private string? word;
    private int countOfOccurences;

    public Word(string word, int countOfOccurences)
    {
      this.word = word;
      this.countOfOccurences = countOfOccurences;
    }

    public int getCount() => countOfOccurences;
    public void addOccurence() => ++countOfOccurences;
    public string? getWord() => word;
    public override string ToString() => "(" + word + ", " + countOfOccurences + ")";
  }

  internal class Program
  {
    static void Main(string[] args)
    {
      List<Word> myList = new List<Word>(); // new()

      myList.printList();
      myList.pushFront(new Word("jedna", 1));
      myList.pushFront(new Word("dva", 1));
      myList.printList();
    }
  }
}

