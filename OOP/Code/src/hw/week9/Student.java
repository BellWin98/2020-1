package hw.week9;

public class Student {
    private String name;
    private int number;
    private double gpa;

    public Student(String name, int number, double gpa){
        this.name = name;
        this.number = number;
        this.gpa = gpa;
    }

    String getName(){
        return name;
    }

    int getNumber(){
        return number;
    }

    double getGpa(){
        return gpa;
    }

    public String toString(){
        return "Name: "+getName()+","+" Number: "+getNumber()+","+" GPA: "+getGpa();
    }
}
