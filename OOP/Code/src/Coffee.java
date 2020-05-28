public class Coffee {
    String origin;
    int degreeOfRoast;
    int grade;
    Coffee(String origin){
        this.origin = origin;
    }
    public void roast() {
        System.out.println("roasting..." + origin);
    }
    public void grind() {
        System.out.println("grinding..." + origin);
    }
    public void brew() {
        System.out.println("brewing..." + origin);
    }
}
