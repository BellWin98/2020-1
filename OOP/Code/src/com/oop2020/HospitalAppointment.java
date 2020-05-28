package com.oop2020;
import java.time.LocalDateTime;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/27
 */
public class HospitalAppointment {
    private Doctor doctor;
    private Patient patient;
    private LocalDateTime localDateTime;

    public HospitalAppointment(Doctor doctor, Patient patient, LocalDateTime localDateTime){
        this.doctor = doctor;
        this.patient = patient;
        this.localDateTime = localDateTime;
    }

    public Doctor getDoctor() {
        return doctor;
    }

    public LocalDateTime getLocalDateTime() {
        return localDateTime;
    }

    public Patient getPatient() {
        return patient;
    }

    public String toString(){
        return "HospitalAppointment: "+localDateTime+"\n"+doctor+"\n"+patient;
    }
}
