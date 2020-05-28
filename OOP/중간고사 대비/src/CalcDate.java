import java.text.SimpleDateFormat;
import java.util.Date;

public class CalcDate {
    public static void main(String[] args){
        Date time = new Date();
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        System.out.println(format.format(time));
        
    }
}
