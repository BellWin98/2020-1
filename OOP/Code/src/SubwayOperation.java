class Subway{
    int line;
    void setLine(int line){
        this.line = line;
    }
    void run(){
        System.out.println(line +" line runs");
    }
}
public class SubwayOperation {
    public static void main(String[] args){
        Subway s = new Subway();
        s.setLine(1);
        s.run();
    }
}
