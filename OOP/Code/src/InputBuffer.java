import java.util.Scanner;
public class InputBuffer {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String s = sc.next(); // 공백 제거 후 출력
        System.out.println("Input str: "+s);
        int num = sc.nextInt(); // 공백 제거 후 출력
        System.out.println("Input num: "+num);
        String s1 = sc.nextLine(); // 공백을 제거하지 않고 출력
        System.out.println("Remaining string: "+s1);
    }
}
