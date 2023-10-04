enum worldSide{North, South, East, West}
public class Main {
    static void info(worldSide direction)
    {
        switch (direction)
        {
            case North :
                System.out.println("There will be cold");
                break;
            case South:
                System.out.println("There will be hot");
                break;
            default:
                System.out.println("It's ehh");
        }
    }
    public static void main(String[] args) {
        worldSide direction = worldSide.North;
        info(direction);
        System.out.println(direction);
        System.out.println(direction.ordinal());
    }
}