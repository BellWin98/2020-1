public class CoffeeOperation {
    public static void main(String[] args){
        Coffee brazilCoffee = new Coffee("Brazil");
        brazilCoffee.roast();
        brazilCoffee.grind();
        brazilCoffee.brew();
    }
}
