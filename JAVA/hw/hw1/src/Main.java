public class Main {
    public static void main(String[] args) {
        LinkedList l1 = new LinkedList();
        System.out.println(l1.isEmpty());

        l1.pushFront(10);
        l1.pushFront(20);
        l1.pushFront(30);
        l1.pushBack(-23);
        l1.pushBack(230);
        l1.pushFront(144);
        l1.pushBack(2);
        l1.myPrint();

        System.out.println(l1.isEmpty());

        System.out.println("Largest is: " + l1.findLargest().toString());
        System.out.println("Smallest is: " + l1.findSmallest().toString());
        l1.emptyList();
        l1.myPrint();
    }
}