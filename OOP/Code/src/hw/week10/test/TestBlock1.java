package hw.week10.test;

import hw.week10.Rectangle;

import java.awt.*;

public class TestBlock1 {

    private hw.week10.Rectangle[] rectangles = new hw.week10.Rectangle[4];
    int count = 0;

    public TestBlock1(Point p){

    }

    public TestBlock1(int x, int y){
        rectangles[0] = new hw.week10.Rectangle(new Point(x, y), new Point(x+ hw.week10.Rectangle.WIDTH, y+ hw.week10.Rectangle.HEIGHT));
        rectangles[1] = new hw.week10.Rectangle(new Point(x+ hw.week10.Rectangle.WIDTH, y), new Point(x+ hw.week10.Rectangle.WIDTH*2,y+ hw.week10.Rectangle.HEIGHT));
        rectangles[2] = new hw.week10.Rectangle(new Point(x, y+ hw.week10.Rectangle.HEIGHT), new Point(x+ hw.week10.Rectangle.WIDTH,y+ hw.week10.Rectangle.HEIGHT*2));
        rectangles[3] = new hw.week10.Rectangle(new Point(x+ hw.week10.Rectangle.WIDTH, y+ hw.week10.Rectangle.HEIGHT), new Point(x+ hw.week10.Rectangle.WIDTH*2,y+ hw.week10.Rectangle.HEIGHT*2));
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
