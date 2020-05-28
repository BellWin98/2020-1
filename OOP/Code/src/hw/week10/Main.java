package hw.week10;

import java.awt.Point;

public class Main {
    public static void main(String[] args){
        Block1 block1 = new Block1(10,10);
        Block2 block2 = new Block2(10,10);
        Block3 block3 = new Block3(10, 10);
        Rectangle r = new Rectangle(new Point(10,10));
        Rectangle r2 = new Rectangle(new Point(20, 20), new Point(70,70));

        System.out.println("r");
        System.out.println(r);
        System.out.println("r2");
        System.out.println(r2);
        System.out.println("\n");
        System.out.println("block1");
        do {
            System.out.println(block1);
            block1.count++;
        } while(block1.count<block1.getRectangles().length);
        block1.count = 0;
        block1.translate(10, -10);
        System.out.println("block1");
        do {
            System.out.println(block1);
            block1.count++;
        } while(block1.count<block1.getRectangles().length);
        System.out.println("\n");
        System.out.println("block2");
        do {
            System.out.println(block2);
            block2.count++;
        } while(block2.count<block2.getRectangles().length);
        block2.count = 0;
        block2.translate(10, -10);
        System.out.println("block2");
        do {
            System.out.println(block2);
            block2.count++;
        } while(block2.count<block2.getRectangles().length);
        System.out.println("\n");
        System.out.println("block3");
        do {
            System.out.println(block3);
            block3.count++;
        } while(block3.count<block3.getRectangles().length);
        block3.count = 0;
        block3.translate(10, -10);
        System.out.println("block3");
        do {
            System.out.println(block3);
            block3.count++;
        } while(block3.count<block3.getRectangles().length);

    }
}
