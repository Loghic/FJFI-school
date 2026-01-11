namespace Ctvrty
{
  internal class Point : GraphicalObject
  {
    public int X { get; set; }
    public int Y { get; set; }

    public Point(int x, int y, int color) : base(color)
    {
      X = x;
      Y = y;
    }

    public override void Draw()
    {
      base.Draw();
      Console.Write(" ({0}, {1})", X, Y);
    }

    public override Point CopyOfObject()
    {
      return new Point(X, Y, Color);
    }
  }
}
