public class TestStaticHelloCounter {
    public static void main(String[] args) {
        StaticHelloCounter h1 = new StaticHelloCounter("world");
        System.out.println("counter: " + h1.getCount());
        StaticHelloCounter h2 = new StaticHelloCounter("new world");
        System.out.println("count 1: " + h1.getCount());
        System.out.println("count 2: " + h2.getCount());
        h1.sayHello();
        h2.sayHello();
    }
}
