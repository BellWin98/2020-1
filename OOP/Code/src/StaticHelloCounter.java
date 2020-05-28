public class StaticHelloCounter {
    private String name;
    private static int count = 0;
    StaticHelloCounter(String name) {
        this.name = name;
        count++;
    }
    void sayHello() {
        System.out.println("hello " + name);
    }
    int getCount() {
        return count;
    }

}
