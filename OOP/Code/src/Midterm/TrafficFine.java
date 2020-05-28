package Midterm;
/* Name: JongSeung Han
   Student ID: 201710736
 */
public class TrafficFine {
    int sum = 0;
    private String car;
    Violation violation = new Violation();

    public int CalcFine(){
        for (int i = 0; i<10; i++){
            int randomCar = (int) Math.floor(Math.random() * 3) + 1;
            violation.b = true;
            violation.RandomViolation();
            TrafficFineTable randViolation = violation.getRandomViolation();
            switch (randomCar){
                case 1:
                    setCar("VAN");
                    System.out.println("car: "+getCar()+","+" violation: "+randViolation+","+" fine: "+randViolation.getVAN());
                    sum += randViolation.getVAN();
                    continue;
                case 2:
                    setCar("CAR");
                    System.out.println("car: "+getCar()+","+" violation: "+randViolation+","+" fine: "+randViolation.getCAR());
                    sum += randViolation.getCAR();
                    continue;
                case 3:
                    setCar("AUTO");
                    System.out.println("car: "+getCar()+","+" violation: "+randViolation+","+" fine: "+randViolation.getAUTO());
                    sum += randViolation.getAUTO();
                    continue;
                default:
            }
        }
        return sum;
    }

    public String getCar() {
        return car;
    }

    public void setCar(String car) {
        this.car = car;
    }
}
