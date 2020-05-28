package com.my.hello;
public class Hello {
        String toWhom = "Heaven!";
        public Hello(){
            System.out.println("default constructor");
        }
        public Hello(String toWhom){
            System.out.println("constructor overloading");
            this.toWhom = toWhom;
        }

        public void setWhom(String toWhom){
            this.toWhom = toWhom;
        }
        public void sayHello(){
            System.out.println("Hello "+toWhom);
        }
}
