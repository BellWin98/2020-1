import java.util.Scanner;
public class Array7 {
    public static void main(String[] args){
        double[] arr = new double[4];
        for (int i = 0; i<arr.length; i++){
            arr[i] = 1.1 *(i + 1);
        }
        System.out.printf("array size: %d\n", arr.length);
        for (int i = 0; i<arr.length; i++){
            System.out.printf("arr[%d] = %.1f\n", i, arr[i]);
        }
    }
}
