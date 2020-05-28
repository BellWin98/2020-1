import java.util.Scanner;

public class SubstitutionAnswer1 {
    public static void main(String[] args){
        String s = "Let's meet in my office at 10";
        System.out.println("You can replace the string in a sentence.");
        System.out.println("Source: "+s);
        Scanner sc = new Scanner(System.in);
        System.out.print("\tEnter a string to replace: ");
        String srcWord = sc.nextLine();
        System.out.print("\tReplace with: ");
        String destWord = sc.nextLine();
        int srcPos = s.indexOf(srcWord);
        String dest1 = s.substring(0, srcPos);
        String dest2 = s.substring(srcPos+srcWord.length());
        String newStr = dest1 + destWord + dest2;
        System.out.printf("\t...replacing %s with %s", srcWord, destWord);
        System.out.print("\nReplaced: "+newStr);
    }
}
