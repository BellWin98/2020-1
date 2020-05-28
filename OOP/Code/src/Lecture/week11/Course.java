package Lecture.week11;
/**
 * @author JongSeung Han 201710736
 * @since 2020/05/25
 */
public class Course {
    private final static int MAX_STUDENTS = 30;
    private int numEnrolled = 0;
    private String lecturer;
    private String room;
    private Student[] students = new Student[MAX_STUDENTS];

    Course(String lecturer, String room){
        this.lecturer = lecturer;
        this.room = room;
    }

    public void setRoom(String room) {
        this.room = room;
    }

    public void enroll(Student student){
        if(numEnrolled<MAX_STUDENTS){
            students[numEnrolled] = student;
            numEnrolled++;
        }
    }

    public void drop(Student student){
        if (numEnrolled>0){
            for (int i =0; i<students.length; i++){
                if (students[i] == student){
                    for (int j = i+1; j<students.length; j++){
                        students[j-1] = students[j];
                    }
                    numEnrolled--;
                    break;
                }
            }
        }
    }

    public int getNumEnrolled(){
        return numEnrolled;
    }

    public void printEnrolled(){
        for (int i =0; i<numEnrolled; i++){
            System.out.println(students[i]);
        }
    }

    public void printLecturer(){

    }
}

