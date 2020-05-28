import java.util.Scanner;

public class MovieTicketPrice {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter prime, standard or economy: ");
        String zone = sc.nextLine();

        if (zone.compareTo("prime")==0){
            System.out.println("The price for prime is 11000.");
        } else if (zone.compareTo("standard") == 0){
            System.out.println("The price for prime is 10000.");
        } else if(zone.compareTo("economy") == 0){
            System.out.println("The price for prime is 9000.");
        } else {
            System.out.println("Wrong input!");
        }
    }
}
