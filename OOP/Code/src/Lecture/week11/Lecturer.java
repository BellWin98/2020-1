package Lecture.week11;

public class Lecturer {
    private String name;
    private String room;
    private String email;

    Lecturer(String name, String room, String email){
        this.name = name;
        this.room = room;
        this.email = email;
    }

    public String getName() {
        return name;
    }

    public String getRoom() {
        return room;
    }

    public String getEmail() {
        return email;
    }
}
