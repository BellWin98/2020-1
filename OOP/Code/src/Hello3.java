
public class Hello3 {
    private String toWhom;
    private HelloCounter counter;
    Hello3(String whom, HelloCounter counter) {
        this.toWhom = whom;
        this.counter = counter;
        counter.increase();
    }
    void sayHello() {
        System.out.println("hello " + toWhom);
    }
    int getCount() {
        return counter.getCount();
    }

}
