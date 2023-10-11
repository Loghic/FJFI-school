import java.util.ArrayList;

public class Picture extends GraphicalObject
{
    private ArrayList<GraphicalObject> picture = new ArrayList<>();

    public Picture()
    {
        super(0);
    }

    public void add(GraphicalObject graphicalObject)
    {
        picture.add(graphicalObject); //pridava na konec
    }

    @Override
    public void draw() {
        for(var go: picture)
        {
            go.draw();
        }
    }
}