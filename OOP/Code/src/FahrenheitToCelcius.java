import java.util.Scanner;
public class FahrenheitToCelcius {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.print("Input Fahrenheit: ");
        float fahrenheit = sc.nextFloat();
        float celsius = ((float) 5/9) * (fahrenheit - 32);
        System.out.printf("Fahrenheit %.2f is %.2f in Celcius\n", fahrenheit, celsius);
    }
}
