/**
 * @author smu
 * @since 202004
 */

import java.util.Scanner;
public class InputInt2 {
    public static void main(String[] args){
        int num;
        Scanner scanner = new Scanner(System.in);

        do {
            System.out.print("Enter an integer (0 to exit): ");
            num = scanner.nextInt();
            if (num!=0){
                System.out.println(num);
            } else{
                break;
            }
        } while(true);
    }
}
