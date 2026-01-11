namespace Ctvrty
{
  internal class Picture : GraphicalObject
  {
    private List<GraphicalObject> picture = new();

    public Picture() : base(0) {}

    public void Add(GraphicalObject go)
    {
      picture.Add(go.CopyOfObject());
    }

    public override void Draw()
    {
      foreach(var go in picture)
      {
        go.Draw();
      }
    }
  }
}
