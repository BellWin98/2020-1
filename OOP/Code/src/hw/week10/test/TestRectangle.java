package hw.week10.test;

import java.awt.*;

public class TestRectangle {
    public static final int WIDTH = 50;
    public static final int HEIGHT = 50;
    private Point upperLeft;
    private Point lowerRight;

    public TestRectangle(Point uL){
        upperLeft = uL;
        lowerRight = new Point(uL.x+WIDTH, uL.y+HEIGHT);
    }

    public TestRectangle(Point uL, Point lR){
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
