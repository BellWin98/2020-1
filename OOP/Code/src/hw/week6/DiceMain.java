package hw.week6;

import java.util.Scanner;
class Dice{

    int numberOfRolling;
    int dice;
    int sum = 0;

    Dice(int numberOfRolling){
        this.numberOfRolling = numberOfRolling;
    }

    void roll(){
        for (int i = 0; i<numberOfRolling; i++){
            dice = (int) Math.floor(Math.random() * 6)+1;
            System.out.print("Roll the dice...");
            System.out.println("\t\tYou got "+dice);
            sum += dice;
        }
    }
}


public class DiceMain {
    public static void main(String[] args){
        System.out.print("\nPlease enter the number of dice you want to throw: ");
        Scanner sc = new Scanner(System.in);
        int roll = sc.nextInt();
        Dice dc = new Dice(roll);
        System.out.println("\n\t\tRoll the dice "+roll+" times!");
        System.out.println("-----------------------------------------------------");
        dc.roll();
        System.out.println("-----------------------------------------------------");
        System.out.println("\t\"The sum of the eyes on the dice is "+dc.sum+"\"");
        if (dc.sum%2 == 0){
            System.out.println("\n\tIt's an even number! Take the bus!");
        }
        else{
            System.out.println("\n\tIt's an odd number! Take the subway!");
        }



    }


}
