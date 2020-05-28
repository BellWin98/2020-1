package Lecture.week11;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/26
 */
public class Customer {
    private String name;
    private String phoneNo;
    private int nVisit;

    public Customer(String name, String phoneNo){
        this.name = name;
        this.phoneNo = phoneNo;
        nVisit = 0;
    }

    public String getName() {
        return name;
    }

    public String getPhoneNo() {
        return phoneNo;
    }

    public int increaseVisit(){
        nVisit++;
        return nVisit;
    }

    public void resetVisit(){
        nVisit = 0;
    }
}
