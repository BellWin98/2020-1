public class Dice {

    private int dice;

    void setDice(int dice){
        this.dice = dice;
    }

    int getDice(){
        return dice;
    }

    int getRollNum(){
        return 5;
    }

    void diceRoll(){
        for (int i = 0; i<getRollNum(); i++){
            dice = (int) Math.floor(Math.random() * 6)+1;
            setDice(dice);
        }
    }
}
