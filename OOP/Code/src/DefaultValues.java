class DefVal{
    int n;
    double d;
    char ch;
    String s;
    boolean b;

    void outputValues() {
        System.out.println("n = " + n);
        System.out.println("d = " + d);
        System.out.println("ch = " + ch);
        System.out.println("s = " + s);
        System.out.println("b = " + b);
    }
}
public class DefaultValues {
    public static void main(String[] args){
        DefVal dv = new DefVal();
        dv.outputValues();
    }
}
