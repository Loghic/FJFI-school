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

    public sealed override void Draw()
    {
      Console.Write("[{0}] ({1}, {2})",Color, X, Y);
    }

    public override Point CopyOfObject()
    {
      return new Point(X, Y, Color);
    }
  }
}
