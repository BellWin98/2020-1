package Lecture.week11;

import java.time.LocalDateTime;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/25
 */
public class Appointment {
    private LocalDateTime time;
    private Person person;
    private Place place;
    Appointment(LocalDateTime time, Person person, Place place){
        this.time = time;
        this.person = person;
        this.place = place;
    }
    public String toString(){
        return "DateTime: " + time.toString() + "\nPerson: " + person.toString() + "\nPlace: " + place.toString();
    }
}
