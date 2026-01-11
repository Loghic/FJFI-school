namespace Ctvrty
{
  internal class Program
  {
    static void Main(string[] args)
    {
      Picture pic = new();
      Point b = new Point(1, 2, 3);
      Line l = new Line(b, new Point(5,6,7), 88);
      pic.Add(b);
      pic.Add(b);
      pic.Add(l);
      pic.Draw();
      Console.WriteLine();

      b.Color = 999;
      pic.Draw();
      Console.WriteLine();


    }
  }
}
