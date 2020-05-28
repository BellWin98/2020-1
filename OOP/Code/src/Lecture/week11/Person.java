package Lecture.week11;
/**
 * @author JongSeung Han 201710736
 * @since 2020/05/25
 */
public class Person {
    private String name;
    private String phone;
    public Person(String name, String phone) {
        this.name = name;
        this.phone = phone;
    }
    public String getName() { return name; }
    public String getPhoneNumber() { return phone; }
    public String toString() {
        return "Name: " + name + " Phone: " + phone;
    }
}
