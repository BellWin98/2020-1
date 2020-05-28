package hw.week10;
import java.awt.Point;

public class Rectangle {

   public static final int WIDTH = 50;
   public static final int HEIGHT = 50;
   private Point upperLeft;
   private Point lowerRight;

   public Rectangle(Point uL){
       upperLeft = uL;
       lowerRight = new Point(uL.x+WIDTH, uL.y+HEIGHT);
   }

   public Rectangle(Point uL, Point lR){
       upperLeft = uL;
       lowerRight = lR;
   }

   public Point getUpperLeft(){
       return upperLeft;
   }

   public Point getLowerRight(){
       return lowerRight;
   }

   public void translate(int x, int y){
        upperLeft.translate(x, y);
        lowerRight.translate(x, y);
    }

    public String toString(){
       return "UL: "+getUpperLeft()+", "+"LR: "+getLowerRight();
    }
}
