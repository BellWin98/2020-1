package hw.week2;
import java.util.Scanner;

public class QuadraticEquation {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.print("Input first integer: ");
		int a = sc.nextInt();

		System.out.print("Input second integer: ");
		int b = sc.nextInt();

		System.out.print("Input last integer: ");
		int c = sc.nextInt();

		double sqrt = Math.sqrt(Math.pow(b, 2) - 4*a*c);
		System.out.println((-b+sqrt)/(2*a));
		System.out.println((-b-sqrt)/(2*a));
		
		sc.close();

	}

}
