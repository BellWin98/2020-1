public class NumberLessThan100 {
    Boolean isLessThan100(int num){
        return (num<100) ? true : false;
    }
    public static void main(String[] args){
        NumberLessThan100 numberLessThan100 = new NumberLessThan100();
        System.out.println(numberLessThan100.isLessThan100(50));
        System.out.println(numberLessThan100.isLessThan100(100));
        System.out.println(numberLessThan100.isLessThan100(150));
    }
}
