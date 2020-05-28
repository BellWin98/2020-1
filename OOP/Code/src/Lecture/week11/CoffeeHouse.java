package Lecture.week11;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/26
 */
public class CoffeeHouse {
    private static final int MAX_ORDER = 100;
    private String name;
    private String phoneNo;
    private String address;
    private Order[] orders;
    private int nOrder;
    private int nLike;

    public CoffeeHouse(String name, String phoneNo, String address){
        this.name = name;
        this.phoneNo = phoneNo;
        this.address = address;
        orders = new Order[MAX_ORDER];
        nOrder = 0;
        nLike = 0;
    }

    public String getPhoneNo() {
        return phoneNo;
    }

    public String getAddress() {
        return address;
    }

    public int getnLike() {
        return nLike;
    }

    public void addOrder(Order order){
        if (nOrder<MAX_ORDER){
            orders[nOrder] = order;
            nOrder++;
        }
    }

    public int increaseLike(){
        nLike++;
        return nLike;
    }
}
