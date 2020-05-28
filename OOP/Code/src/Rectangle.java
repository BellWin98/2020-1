/*
class Rectangle{
    -height: double
    -width: double
    -area: double
    Rectangle(h: double, w: double)
    getArea(): double
    getHeight(): double
    setHeight(double: h): void
    getWidth(): double
    setWidth(double w): void
}
 */

public class Rectangle {
    private double width;
    private double height;
    private double area;

    Rectangle(double width, double height){
        this.width = width;
        this.height = height;
}

    double getArea(){
        return area;
    }

    double getHeight(){
        return height;
    }
    void setHeight(double height){
        this.height = height;
        // area = width*this.height;
        calcArea();
    }

    double getWidth(){
        return width;
    }
    void setWidth(double width){
        this.width = width;
        // area = width*this.height;
        calcArea();
    }

    private void calcArea(){
        area = width*this.height;
    }
}
