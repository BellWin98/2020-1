package com.my.app;
import com.my.hello.Hello;

public class Main {
	public static void main(String[] args){
		Hello h = new Hello();
		Hello h1 = new Hello("jsl");
		// Hello2 h1 = new Hello2();
		 h.setWhom("jsl");
		// h1.setWhom("jsl2");
		 h.sayHello();
		 h1.sayHello();
	}
}
