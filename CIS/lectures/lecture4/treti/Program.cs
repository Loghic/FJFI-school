// Enhancing method
//
namespace helper
{
  // It is hidden in helper namespace
  // It does not depend on class name (it is not used)
  public static class Helper
  {
    public static void Print(this string text)
    {
      if (text == null) text = "";
      Console.WriteLine(text);
    }
  }

}
namespace Treti
{
  using helper;

  internal class Program
  {
    static void Main(string[] args)
    {
      string txt = "Nazdar";
      txt.Print();
    }
  }
}
