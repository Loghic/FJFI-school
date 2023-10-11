public class Main
{
    private static void doControl(Control controlledObject)
    {
        controlledObject.zkontroluj();
//        Point b = (Point) controlledObject; // works for point but not for text
        // It's possible for point but for file it throws and exception
    }

    private static void call(Showcase showcase)
    {
        System.out.println(showcase.calculate(5));
    }

    public static void main(String[] args)
    {
        System.out.println(Control.COUNT);
        Point b = new Point(0,0);
        File f = new File(null);
        doControl(b);
        doControl(f);
        b.defaultControl();
        f.defaultControl();
        b.randomTest();
        Control.message("Testing interface");
        doControl(()->{System.out.println("Showcase of lambda function");});
        call((x)->x+1); // call ((x)->{x+1;}); it can be shorten like this
    }
}