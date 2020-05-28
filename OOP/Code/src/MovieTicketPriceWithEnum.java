import java.util.Scanner;

enum Zone {STANDARD, PRIME, ECONOMY}
public class MovieTicketPriceWithEnum {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter 'prime', 'standard', or 'economy': ");
        String zoneString = scanner.next();
        Zone zone = Zone.valueOf(zoneString.toUpperCase());
        switch(zone){
            case PRIME:
                System.out.println("Ticket price for prime is 11000");
                break;
            case STANDARD:
                System.out.println("Ticket price for prime is 10000");
                break;
            case ECONOMY:
                System.out.println("Ticket price for prime is 9000");
                break;
            default:
                System.out.println("[WARN] wrong import!");
                break;

        }
    }
}
