public interface Control
{
    final int COUNT = 21;
    public void zkontroluj();

    default void defaultControl() // its not needed for it to be void; it can be  bool etc.
    {
        System.out.println("Default control has been done!");
    }
    default
    void randomTest()
    {
        System.out.println("Weee, weee, let's go, test");
    }

    static void message(String text)
    {
        System.out.println("The message: " + text + ". Has been sent!");
    }
}

interface Showcase
{
    int calculate(int m);
}
