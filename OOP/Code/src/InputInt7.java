import java.util.Scanner;
public class InputInt7 {
    public static void main(String[] args){
        int num;
        Scanner scanner = new Scanner(System.in);

        do {
            System.out.print("Enter an integer (any number less than 100 to exit except 0): ");
            num = scanner.nextInt();
            if (num == 0) {
                continue;
            } else{
                System.out.println(num);
            }
        } while(num<100);
    }
}
