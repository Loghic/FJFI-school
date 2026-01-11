namespace Prvni
{
  internal class Line : GraphicalObject
  {
    public Point Start, End;

    public override void Draw()
    {
      Console.Write("<");
      Console.Write("[{0}]", Color);
      Start.Draw();
      End.Draw();
      Console.Write(">");
    }

    public Line(int x1, int y1, int x2, int y2, int color) : base(color)
    {
      Start = new Point(x1, y1, color);
      End = new Point(x2, y2, color);
    }

    public Line(Point start, Point end, int color): base(color)
    {
      Start = start.CopyOfObject();
      End = end.CopyOfObject();
    }

    public override Line CopyOfObject()
    {
      return new Line(Start, End, Color);
    }

    public override object Clone()
    {
      Line res = (Line)MemberwiseClone();
      // Line res = MemberwiseClone() as Line; // also possible
      res.Start = (Point)Start.Clone();
      res.End = (Point)End.Clone();
      return res;
    }

  }
}
