public class ConvertFahrenheit23 {
    public static void main(String[] args){
        float fahrenheit = 23;
        float celsius = ((float) 5/9) * (float) (fahrenheit - 32);
        System.out.printf("Fahrenheit %.2f is %.2f in Celcius\n", fahrenheit, celsius);
    }
}
