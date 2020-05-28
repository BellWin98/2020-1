package hw.week5;

class CardDeck {
    int card;
    String cardShape;

    CardDeck(String cardShape){
        this.cardShape = cardShape;
    }

    void setCard(int[] card){
        this.card = card.length;
    }

    void deal(){
        System.out.println("Card Remaining: "+card);
        do {
            int randomNum = (int) Math.floor(Math.random() * 9) + 2;
            System.out.println("\nGive out a card.");
            card -= 1;
            System.out.println("========================================");
            System.out.println("\tYou got " + cardShape + " (Card Number: " + randomNum + ")");
            System.out.println("\tRecent Card Remaining: " + card);
        } while (card != 1);
    }
}



public class CardMain {
    public static void main(String[] args){
        CardDeck cd = new CardDeck("Diamonds");
        cd.setCard(new int[3]);
        cd.deal();
    }
}

