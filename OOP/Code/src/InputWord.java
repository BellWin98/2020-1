import java.util.Scanner;

public class InputWord {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String word;
        System.out.print("Input word: ");
        word = sc.nextLine();
        while (!word.equals("quit")) {
            System.out.println(word);
            System.out.println("Enter a word to repeat(Enter 'quit' to finish): " +word);
            System.out.print("Input word: ");
            word = sc.nextLine();
        }

    }
}
