package hw.week4;
import java.util.Scanner;

public class Substitution {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String s = "Let's meet in my office at 10";
		System.out.println("���� ���忡�� ���ڿ��� �ٲٴ� ���α׷��Դϴ�.");
		System.out.println("��������: "+s);
		System.out.println("���忡�� �ٲٰ� ���� ���ڿ��� �Է��ϼ���: ");
		String s1 = sc.nextLine();
		System.out.println("���ο� ���ڿ��� �Է��ϼ���: ");
		String s2 = sc.nextLine();
		System.out.println("���ο� ����: "+s.replace(s1, s2));
		
		sc.close();
		
		
		
	}
}
