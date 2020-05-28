package Midterm;
/* Name: JongSeung Han
   Student ID: 201710736
 */
public class MidtermMain {
    public static void main(String[] args) {
        TrafficFine trafficFine = new TrafficFine();

        System.out.printf("CASE 1: fine: %d\n", TrafficFineTable.OVER2040.getAUTO());
        System.out.printf("CASE 2: fine: %d\n", TrafficFineTable.LIGHT.getVAN() + TrafficFineTable.YELLOW.getVAN());
        System.out.printf("CASE 3: fine: %d\n", TrafficFineTable.BUSONLYHIGHWAY.getCAR() + TrafficFineTable.OVER60.getCAR());
        System.out.println("Total fine: "+trafficFine.CalcFine());
    }
}



