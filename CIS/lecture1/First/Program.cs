namespace First
{
  internal class Program
  {


    static void Main(string[] args)
    {
      try {
        Console.Write("Input whole number: ");
        int n = Tools.ReadNumber();
        Console.WriteLine("The factorial of number " + n +  " is: " + Tools.Factorial(n));
      } catch (Exception e) {
        Console.WriteLine(e.Message);
      }

    }
  }
}


