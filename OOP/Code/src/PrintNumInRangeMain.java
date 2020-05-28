import java.util.Scanner;

public class PrintNumInRangeMain {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        PrintNumInRange printNumInRange = new PrintNumInRange(scanner);
        printNumInRange.readInt();
        if (printNumInRange.isInRange(1,100)){
            printNumInRange.printInt();
        } else{
            System.out.println("Out of range 1~100");
        }
    }
}
