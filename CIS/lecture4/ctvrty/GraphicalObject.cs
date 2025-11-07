using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ctvrty
{
  internal class GraphicalObject
  {
    public int Color
    {
      get; set;
    }

    public GraphicalObject(int color) => Color = color;

    public virtual void Draw()
    {
      Console.Write("[{0}]", Color);
    }

    public virtual GraphicalObject CopyOfObject()
    {
      return new GraphicalObject(Color);
    }

  }
}
