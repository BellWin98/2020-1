package com.oop2020;
import java.util.Date;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/27
 */
public class Patient {
    private String name;
    private String id;

    public Patient(String name){
        this.name = name;
        Date date = new Date();
        makeId(date);
    }

    public String getName() {
        return name;
    }

    public String getId() {
        return id;
    }

    public void makeId(Date date){
        id = date.getTime()+name;
    }

    public String toString(){
        return "Patient name: "+name+" id: "+id;
    }
}
