package Lecture.week11;

public class Course2Main {
    public static void main(String[] args){
        Lecturer lecturer = new Lecturer("JongSeung Han", "G306", "hjs1351@naver.com");
        Course2 course = new Course2(lecturer, "G305");
        Student student1 = new Student("201910736", "John Bade");
        Student student2 = new Student("201910737", "Trevor Purman");
        course.enroll(student1);
        System.out.println(course.getNumEnrolled());
        course.enroll(student2);
        System.out.println(course.getNumEnrolled());
        course.printEnrolled();

    }
}
