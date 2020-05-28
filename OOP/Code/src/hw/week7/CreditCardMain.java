package hw.week7;
import java.util.Scanner;

enum CreditCard{
    CJONE_SAMSUNG(30,1), CJONE_SHINHAN(30,1), THE_CJ(20,2),
    SAMSUNG_6_V4(20,0), SHINHAN_LADY(20,0), KB_STAR(20,0),
    EMART_KB(15,0);

    private int discountRate;
    private int reserveRate;

    CreditCard(int discountRate, int reserveRate){
        this.discountRate = discountRate;
        this.reserveRate = reserveRate;
    }

    public int getDiscountRate(){
        return discountRate;
    }

    public int getReserveRate(){
        return reserveRate;
    }
}

public class CreditCardMain {
    public static void main(String[] args){
        CreditCard cd;
        Scanner sc = new Scanner(System.in);
        System.out.print("Input card: ");
        String cardName = sc.nextLine();

        switch (cardName){
            case "CJ ONE SamSung Card":
                cd = CreditCard.CJONE_SAMSUNG;
                System.out.printf("DiscountRate: %d, ReserveRate: %d\n", cd.getDiscountRate(), cd.getReserveRate());
                break;
            case "CJ ONE ShinHan Card":
                cd = CreditCard.CJONE_SHINHAN;
                System.out.printf("DiscountRate: %d, ReserveRate: %d\n", cd.getDiscountRate(), cd.getReserveRate());
                break;
            case "The CJ":
                cd = CreditCard.THE_CJ;
                System.out.printf("DiscountRate: %d, ReserveRate: %d\n", cd.getDiscountRate(), cd.getReserveRate());
                break;
            case "SamSung 6 V4":
                cd = CreditCard.SAMSUNG_6_V4;
                System.out.printf("DiscountRate: %d, ReserveRate: %d\n", cd.getDiscountRate(), cd.getReserveRate());
                break;
            case "ShinHan Lady":
                cd = CreditCard.SHINHAN_LADY;
                System.out.printf("DiscountRate: %d, ReserveRate: %d\n", cd.getDiscountRate(), cd.getReserveRate());
                break;
            case "KB Star":
                cd = CreditCard.KB_STAR;
                System.out.printf("DiscountRate: %d, ReserveRate: %d\n", cd.getDiscountRate(), cd.getReserveRate());
                break;
            case "E-Mart KB":
                cd = CreditCard.EMART_KB;
                System.out.printf("DiscountRate: %d, ReserveRate: %d\n", cd.getDiscountRate(), cd.getReserveRate());
                break;
            default:
                System.out.println("Card not found.");

        }
    }
}

