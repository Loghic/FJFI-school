using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ctvrty
{
  internal abstract class GraphicalObject
  {
    public int Color
    {
      get; set;
    }

    public GraphicalObject(int color) => Color = color;

    public abstract void Draw();

    public abstract GraphicalObject CopyOfObject();

  }
}
