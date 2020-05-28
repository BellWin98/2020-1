package hw.week2;
import java.util.Scanner;

public class VolumeOfTruncatedCone {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.print("Input radius 1: ");
		double R1 = sc.nextDouble();

		System.out.print("Input radius 2: ");
		double R2 = sc.nextDouble();

		System.out.print("Input height: ");
		double Height = sc.nextDouble();
		
		double pi = 3.14;
		double v = pi*(Math.pow(R1, 2)+R1*R2+Math.pow(R2, 2))/3*Height;
		System.out.println(v);
		
		sc.close();
	}

}
