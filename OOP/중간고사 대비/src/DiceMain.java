public class DiceMain {
    public static void main(String[] args){

        int sum1 = 0;
        int sum2 = 0;
        Dice dice = new Dice();
        System.out.print("A: ");
        for (int i = 0; i<dice.getRollNum();i++){
            dice.diceRoll();
            System.out.print(dice.getDice()+" ");
            sum1+=dice.getDice();
        }
        System.out.println(" sum: "+sum1);

        System.out.print("B: ");
        for (int i = 0; i<dice.getRollNum();i++){
            dice.diceRoll();
            System.out.print(dice.getDice()+" ");
            sum2+=dice.getDice();
        }
        System.out.println(" sum: "+sum2);

        if (sum1>sum2){
            System.out.println("A wins");
        } else if (sum2>sum1){
            System.out.println("B wins");
        } else{
            System.out.println("Draw");
        }
    }
}
