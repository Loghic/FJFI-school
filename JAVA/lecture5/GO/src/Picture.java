import java.util.ArrayList;

public class Picture extends GraphicalObject
{
    private ArrayList<GraphicalObject> picture = new ArrayList<>();

    public Picture()
    {
        super(0);
    }

    @Override
    public GraphicalObject kopie() {
        return null;
    }

    public void add(GraphicalObject graphicalObject)
    {
        picture.add(graphicalObject.kopie()); //pridava na konec
    }

    @Override
    public void draw() {
        for(var go: picture)
        {
            go.draw();
        }
    }
}