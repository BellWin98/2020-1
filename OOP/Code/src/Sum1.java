/*
 * class Diagram
 class Sum1 {
    sum:int=0;
    getSum():int
    add(num:int):int
    printSum():void
}
 */
public class Sum1 {
    int sum = 0;

    int getSum(){
        return sum;
    }

    int add(int num){
        if (num<=50){
            return sum;
        }else if(num>100){
            sum+=num;
        }
        printSum();
        return sum;
    }

    void printSum(){
        System.out.println(getSum());
    }
}
