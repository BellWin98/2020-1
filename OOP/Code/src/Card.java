class CardDec {
    int card;
    String cardShape;

    CardDec(String cardShape){
        this.cardShape = cardShape;
    }

    void setCard(int[] card){
        this.card = card.length;
    }

    void deal(){
        while(true){
            int randomNum = (int) Math.floor(Math.random()*9)+2;
            if (card>0){
                System.out.println("\tCard Remaining: "+card);
                System.out.println("\nGive out a card.");
                System.out.println("========================================");
                System.out.println("\tYou got "+cardShape+ " (Card Number: "+randomNum+")");
                card -= 1;

            } else{
                System.out.println("\tNo cards left.");
                break;
            }
        }
    }
}

public class Card {
    public static void main(String[] args){
        CardDec cd = new CardDec("Diamonds");
        cd.setCard(new int[3]);
        cd.deal();
    }
}
