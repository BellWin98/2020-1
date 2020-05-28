import java.util.Scanner;

public class MovieTicketPriceWithSwitch {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter 'prime', 'standard', or 'economy': ");
        String zone = scanner.next();
        switch(zone){
            case "prime":
                System.out.println("Ticket price for prime is 11000");
                break;
            case "standard":
                System.out.println("Ticket price for prime is 10000");
                break;
            case "economy":
                System.out.println("Ticket price for prime is 9000");
                break;
            default:
                System.out.println("[WARN] wrong import!");
                break;

        }
    }
}
