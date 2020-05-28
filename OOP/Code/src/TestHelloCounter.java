public class TestHelloCounter {
    public static void main(String[] args) {
        HelloCounter counter = new HelloCounter();
        Hello3 h1 = new Hello3("world", counter);
        System.out.println("counter: " + h1.getCount()); 
        Hello3 h2 = new Hello3("new world", counter);
        System.out.println("counter1: " + h1.getCount());
        System.out.println("counter2: " + h2.getCount());
        h1.sayHello();
        h2.sayHello();
    }

}
