public class InitializeTest {
    String s;
    void printString(){
        System.out.println(s);
    }
    public static void main(String[] args){
        InitializeTest s1 = new InitializeTest();
        s1.printString();
    }
}
