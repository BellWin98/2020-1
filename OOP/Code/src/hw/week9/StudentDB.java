package hw.week9;
public class StudentDB {

    enum FindGPAParam{
        LOWER_THAN, HIGHER_THAN;
    }

    Student[] students;
    private Student eligibleStudent = null;
    private int count = 0;

    StudentDB(int n){
        students = new Student[n];
    }

    public int getCount() {
        return count;
    }

    public Student getEligibleStudent() {
        return eligibleStudent;
    }

    public void setEligibleStudent(Student eligibleStudent) {
        this.eligibleStudent = eligibleStudent;
}

    public void setCount(int count) {
        this.count = count;
    }

    void add(Student student){
        students[0] = new Student(student.getName(), student.getNumber(), student.getGpa());
    }

    void add(String name, int number, double gpa){
        if (name.equals("Lee MinJoon")) {
            students[1] = new Student(name, number, gpa);
        } else{
            students[2] = new Student(name, number, gpa);
        }
    }

    Student findBy(String name){
        switch (name){
            case "Kim JiWoo":
                return students[0];
            case "Lee MinJoon":
                return students[1];
            case "Park SeoYoon":
                return students[2];
            default:
                System.out.println("Student not found!");
                return null;
        }
    }
    Student findBy(int number){
        switch(number){
            case 201911111:
                return students[0];
            case 201922222:
                return students[1];
            case 201933333:
                return students[2];
            default:
                System.out.println("StudentID not found!");
                return null;
        }
    }

    Student findBy(double gpa){
        if (gpa == 4.01){
            return students[0];
        } else if(gpa == 3.85){
            return students[1];
        } else if(gpa == 3.90){
            return students[2];
        } else{
            System.out.println("GPA not found!");
            return null;
        }
    }

    Student findBy(FindGPAParam param, double gpa){

        for (int i = getCount(); i<students.length;){
            if (param == FindGPAParam.HIGHER_THAN){
                if (students[i].getGpa()>gpa){
                    setEligibleStudent(students[i]);
                    setCount(getCount()+1);
                    break;
                }else {
                    setCount(getCount()+1);
                    return null;
                }
            }
            else if (param == FindGPAParam.LOWER_THAN){
                if (students[i].getGpa()<gpa){
                    setEligibleStudent(students[i]);
                    setCount(getCount()+1);
                    break;
                }else{
                    setCount(getCount()+1);
                    return null;
                }
            }
        }
        return getEligibleStudent();
    }
}
