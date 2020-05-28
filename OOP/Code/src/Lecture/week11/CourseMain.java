package Lecture.week11;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/25
 */
public class CourseMain {
    public static void main(String[] args){
        Course course = new Course("BellWin", "G305");
        Student student1 = new Student("201910736", "John Bade");
        Student student2 = new Student("201910737", "Trevor Purman");
        course.enroll(student1);
        System.out.println(course.getNumEnrolled());
        course.enroll(student2);
        System.out.println(course.getNumEnrolled());
        course.printEnrolled();

    }
}
