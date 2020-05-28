import java.util.Scanner;

public class Divisor1 {
    public static void main(String[] args){
        int num1;
        int num2;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter two integers: ");
        num1 = sc.nextInt();
        num2 = sc.nextInt();
        if ((num2%num1) == 0){
            System.out.printf("%d is divisor of %d.", num1, num2);
        } else{
            System.out.printf("%d is not a divisor of %d.", num1, num2);
        }
    }
}
