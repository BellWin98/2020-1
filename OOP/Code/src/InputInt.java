import java.util.Scanner;

public class InputInt {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int num;
        do {
            System.out.printf("Enter an integer (0 to finish): ");
            num = sc.nextInt();
            System.out.println(num);
        } while (num!=0);
    }
}
