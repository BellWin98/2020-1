package hw.week10.test;

import java.awt.*;

public class TestMain {
    public static void main(String[] args){
        TestBlock1 testBlock1 = new TestBlock1(10,10);
        TestRectangle r = new TestRectangle(new Point(10,10));
        TestRectangle r2 = new TestRectangle(new Point(20, 20), new Point(70,70));

        System.out.println("r");
        System.out.println(r);
        System.out.println("r2");
        System.out.println(r2);
        System.out.println("testBlock1");

        System.out.println(testBlock1);

    }

}
