package com.oop2020;

/**
 * @author JongSeung Han 201710736
 * @since 2020/05/27
 */
public class Doctor {
    private String name;
    private String id;

    public Doctor(String id,String name){
        this.name = name;
        this.id = id;
    }

    public String getName(){
        return name;
    }

    public String getId(){
        return id;
    }

    public String toString(){
        return "Doctor name: "+name+" id: "+id;
    }
}
