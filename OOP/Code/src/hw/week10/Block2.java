package hw.week10;

import java.awt.Point;

public class Block2 {
    private Rectangle[] rectangles = new Rectangle[4];
    int count = 0;

    public Block2(int x, int y){
        rectangles[0] = new Rectangle(new Point(x, y), new Point(x+Rectangle.WIDTH, y+Rectangle.HEIGHT));
        rectangles[1] = new Rectangle(new Point(x, y+Rectangle.HEIGHT), new Point(x+Rectangle.WIDTH,y+Rectangle.HEIGHT*2));
        rectangles[2] = new Rectangle(new Point(x, y+Rectangle.HEIGHT*2), new Point(x+Rectangle.WIDTH,y+Rectangle.HEIGHT*3));
        rectangles[3] = new Rectangle(new Point(x, y+Rectangle.HEIGHT*3), new Point(x+Rectangle.WIDTH,y+Rectangle.HEIGHT*4));
    }

    public void translate(int x, int y){
        for (int i = 0; i<rectangles.length; i++){
            rectangles[i].getLowerRight().translate(x, y);
            rectangles[i].getUpperLeft().translate(x, y);
        }
    }

    public Rectangle[] getRectangles() {
        return rectangles;
    }

    public String toString(){
        return "UL: "+rectangles[count].getUpperLeft()+", "+"LR: "+rectangles[count].getLowerRight();
    }
}
