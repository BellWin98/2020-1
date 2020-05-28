package hw.week9;
import java.util.Scanner;
public class StudentMain {
    public static void main(String[] args){
        StudentDB studentDB = new StudentDB(3);
        Student student = new Student("Kim JiWoo", 201911111, 4.01);
        Scanner scanner = new Scanner(System.in);

        boolean b = true;
        String studentName;
        int studentID, num, decision, i;
        double gpa, standardGPA;
        Student studentByName, studentByStudentID, studentByGPA, studentByStandard;

        studentDB.add(student);
        studentDB.add("Lee MinJoon", 201922222, 3.85);
        studentDB.add("Park SeoYoon", 201933333, 3.90);

        System.out.println("\nSelect the number of information you want to input");
        System.out.println("\n1. Name | 2. StudentID | 3. GPA | 4. Search for students below(over) certain GPA");
        num = scanner.nextInt();
        scanner.nextLine(); // A solution of the problem when using nextLine() right after using nextInt().
        // The Scanner.nextInt method does not remove the last open letter(enter, newline) of the user input.
        while(b){
        switch(num){
            case 1:
                System.out.print("Input Name(Option: Kim JiWoo, Lee MinJoon, Park SeoYoon): ");
                studentName = scanner.nextLine();
                studentByName = studentDB.findBy(studentName);
                    if (studentByName!=null){
                    System.out.println(studentByName);
                    b = false;
                    break;
                }
                System.out.println("Please retry");
                continue;

            case 2:
                System.out.print("Input StudentID: ");
                studentID = scanner.nextInt();
                studentByStudentID = studentDB.findBy(studentID);
                if (studentByStudentID!=null){
                    System.out.println(studentByStudentID);
                    b = false;
                    break;
                }
                System.out.println("Please retry");
                continue;

            case 3:
                System.out.print("Input GPA: ");
                gpa = scanner.nextDouble();
                studentByGPA = studentDB.findBy(gpa);
                if (studentByGPA!=null){
                    System.out.println(studentByGPA);
                    b = false;
                    break;
                }
                System.out.println("Please retry");
                continue;

            case 4:
                System.out.print("Input criteria GPA: ");
                standardGPA = scanner.nextDouble();
                System.out.println("Pick a Number either 1. Below or 2. Over");
                decision = scanner.nextInt();
                if (decision == 1){
                    i = 0;
                    while(i<studentDB.students.length){
                        studentByStandard = studentDB.findBy(StudentDB.FindGPAParam.LOWER_THAN, standardGPA);
                        if (studentByStandard!=null){
                            System.out.println(studentByStandard);
                            i++;
                        }else{
                            i++;
                        }
                    }
                    b = false;
                    break;
                } else if (decision == 2){
                    i = 0;
                    while (i<studentDB.students.length){
                        studentByStandard = studentDB.findBy(StudentDB.FindGPAParam.HIGHER_THAN, standardGPA);
                        if (studentByStandard!=null){
                            System.out.println(studentByStandard);
                            i++;
                        }else{
                            i++;
                        }
                    }
                    b = false;
                    break;
                } else{
                    System.out.println("Invalid Input");
                    System.out.println("Please retry");
                    continue;
                }

            default:
                System.out.println("Invalid Input");
                b = false;
                break;
            }
        }
    }
}
