public class TestRectangle {
    public static void main(String[] args){
        Rectangle rectangle = new Rectangle(10, 15);
        double area = rectangle.getArea();
        System.out.println("area = "+area);
        rectangle.setWidth(20);
        area = rectangle.getArea();
        System.out.println("area = "+area);
    }
}
