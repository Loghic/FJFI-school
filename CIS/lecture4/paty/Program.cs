namespace Ctvrty
{
  internal class Program
  {
    static void Main(string[] args)
    {
      GraphicalObject go = new(5);
      go.Draw();
      Console.WriteLine();

      Point p = new(10, -5, 255);
      p.Draw();
      Console.WriteLine();

      GraphicalObject go2 = new Point(2,5,8);
      go2.Draw();
      Console.WriteLine();

      go2 = new Point(color: 254, y: 22, x: 5);
      go2.Draw();
      Console.WriteLine();

      go2 = new Line(1, 2, 3, 4, 5);
      go2.Draw();
      Console.WriteLine();

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
