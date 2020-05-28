package hw.week11;
import com.oop2020.Doctor;
import com.oop2020.HospitalAppointment;
import com.oop2020.Patient;
import java.time.LocalDateTime;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/27
 */

public class TestHospitalAppointment {
    public static void main(String[] args){
        Doctor doctor = new Doctor("10", "Dr. Lim");
        Patient patient = new Patient("cho");
        LocalDateTime d1 = LocalDateTime.of(2020, 5, 20, 13, 30, 0);
        LocalDateTime d2 = LocalDateTime.of(2020, 6, 20, 13, 30, 0);
        LocalDateTime d3 = LocalDateTime.of(2020, 7, 20, 13, 30, 0);
        HospitalAppointment[] has = new HospitalAppointment[3];

        has[0] = new HospitalAppointment(doctor, patient, d1);
        has[1] = new HospitalAppointment(doctor, patient, d2);
        has[2] = new HospitalAppointment(doctor, patient, d3);

        for (HospitalAppointment appointment : has){
            System.out.println(appointment);
        }
    }
}
