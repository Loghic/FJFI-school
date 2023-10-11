public class Main
{
    public static void main(String[] args)
    {
//        GraphicalObject go = new Point(5,6,7);
//        GraphicalObject go = new Abscissa(55, new Point(5,2,1),
//                new Point(4,8,9));
//        go.draw();

        Picture picture = new Picture();
        picture.add(new GraphicalObject(5));
        picture.add(new Abscissa(8,
                    new Point(5,1,3), new Point(8,9,10)));
        //picture.draw();
        //Dalsi problem krom opakujici barvy?
        Point point = new Point(2,5,7);
        picture.add(point);
        picture.draw();
        point.setY(156);
        System.out.println();
        picture.draw();
        // problem, ze se do kontejneru ukladaji odkazy, takze
        // se zmenili ulozene data, aniz bychom menili data v metode
        // takze budeme ukladat kopie
        // zmenou dat mimo, zmenim data v objektu
    }
}