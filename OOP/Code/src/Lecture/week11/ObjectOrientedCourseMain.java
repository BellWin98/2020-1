package Lecture.week11;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/25
 */

public class ObjectOrientedCourseMain {
    public static void main(String[] args){
        ObjectOrientedCourse objectOrientedCourse = new ObjectOrientedCourse("BellWin", "G305");
        objectOrientedCourse.enroll("John Bade");
        System.out.println(objectOrientedCourse.getNumEnrolled());
        objectOrientedCourse.enroll("Trevor Purman");
        System.out.println(objectOrientedCourse.getNumEnrolled());
        objectOrientedCourse.printEnrolled();
    }
}
