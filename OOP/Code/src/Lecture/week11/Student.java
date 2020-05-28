package Lecture.week11;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/25
 */
public class Student {
    private String studentNo;
    private String name;

    Student(String studentNo, String name){
        this.studentNo = studentNo;
        this.name = name;
    }

    public String getStudentNo(){
        return studentNo;
    }

    public String getName(){
        return name;
    }

    public String toString(){
        return "Name: "+name+", "+"Student Number: "+studentNo;
    }

}
