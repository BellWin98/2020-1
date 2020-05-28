import java.util.Scanner;
/*
 * class diagram
    class PrintNumInRange {
    value:int
    scanner:Scanner
    PrintNumInRange(scanner:Scanner)
    isInRange(min:int, max:int):boolean
    printInt():void
    readInt():void
}
 */
public class PrintNumInRange {
    int value;
    Scanner scanner = new Scanner(System.in);

    PrintNumInRange(Scanner scanner) {
        this.scanner = scanner;
    }

    Boolean isInRange(int min, int max) {
        return (value>= min && value<=max) ? true : false;
    }

    void printInt(){
        System.out.println(value);
    }

    void readInt(){
        System.out.print("Enter an integer: ");
        value = scanner.nextInt();
    }
}
