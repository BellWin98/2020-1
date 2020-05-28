package Lecture.week11;

import java.time.LocalDateTime;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/25
 */
public class AppointmentMain {
    public static void main(String[] args){
        LocalDateTime dateTime = LocalDateTime.now();
        LocalDateTime d = LocalDateTime.of(2020, 5, 19, 16, 30, 0);
        Person person = new Person("cho", "111-1111-1111");
        Place place = new Place("jongno", "222-2222-2222");
        Appointment appointment = new Appointment(d, person, place);

        System.out.println(dateTime);
        System.out.println(appointment);
    }

}
