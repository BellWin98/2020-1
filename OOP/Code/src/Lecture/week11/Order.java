package Lecture.week11;

import java.time.LocalDateTime;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/26
 */
public class Order {
    private static final int MAX_VISIT = 10;
    private Customer customer;
    private LocalDateTime orderDateTime;
    private Coffee coffee;
    private int quantity;

    public void takeOrder(Customer customer, Coffee coffee){
        this.customer = customer;
        this.coffee = coffee;
        quantity++;
        int v = customer.increaseVisit();
        if (v>=MAX_VISIT){
            System.out.printf("%d ordered, So you've got another coffee!\n", v);
            customer.resetVisit();
        }
    }

    public int charge(){
        return coffee.getPrice()*quantity;
    }
}
