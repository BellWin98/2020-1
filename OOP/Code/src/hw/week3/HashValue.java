package hw.week3;
import java.util.Scanner;

public class HashValue {
            public static void main(String[] args){
                Scanner sc = new Scanner(System.in);
                char[] s = new char[5];
                double hashValue = 0;
        System.out.println("Input 5 letters one by one in a line ");
        int len = s.length;
        for (int i = 0; i<s.length; i++){
            --len;
            s[i] = sc.next().charAt(0);
            hashValue += s[i]*Math.pow(31, len);
        }
        System.out.printf("The hash value of string "+s[0]+s[1]+s[2]+s[3]+s[4]+" is %.2f ", hashValue);

    }

}

