package Lecture.week11;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/26
 */
public class CoffeeHouseMain {
    public static void main(String[] args){
        CoffeeHouse coffeeHouse = new CoffeeHouse("Starbucks", "02-945-9041", "Nowon-Gu, Seoul");
        Customer customer = new Customer("BellWin", "010-6717-1351");
        Coffee coffee = new Coffee("Americano", 3500);
        Order order = new Order();
        for (int i = 0; i<12; i++){
            order.takeOrder(customer, coffee);
        }
        coffeeHouse.addOrder(order);
        System.out.printf("Your charge will be %d\n", order.charge());
    }

}
