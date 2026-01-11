namespace Prvni
{
  internal class Program
  {
    static void Main(string[] args)
    {
      Point b = new Point(1,2,3);
      Point c = (Point)b.Clone();

      c.Color = 10;
      b.Draw();
      c.Draw();
    }
  }
}
