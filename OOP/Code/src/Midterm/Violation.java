package Midterm;
/* Name: JongSeung Han
   Student ID: 201710736
 */
public class Violation {

    TrafficFineTable randomViolation;
    boolean b = true;
    public void RandomViolation() {
        int num = (int) Math.floor(Math.random() * 9) + 1;
        while(b){
            switch (num) {
                case 1:
                    setRandomViolation(TrafficFineTable.LIGHT);
                    b = false;
                    break;
                case 2:
                    setRandomViolation(TrafficFineTable.PEDESTRIAN);
                    b = false;
                    break;
                case 3:
                    setRandomViolation(TrafficFineTable.YELLOW);
                    b = false;
                    break;
                case 4:
                    setRandomViolation(TrafficFineTable.BUSONLYHIGHWAY);
                    b = false;
                    break;
                case 5:
                    setRandomViolation(TrafficFineTable.LANE);
                    b = false;
                    break;
                case 6:
                    setRandomViolation(TrafficFineTable.OVER60);
                    b = false;
                    break;
                case 7:
                    setRandomViolation(TrafficFineTable.OVER4060);
                    b = false;
                    break;
                case 8:
                    setRandomViolation(TrafficFineTable.OVER2040);
                    b = false;
                    break;
                case 9:
                    setRandomViolation(TrafficFineTable.OVER20);
                    b = false;
                    break;
            }
        }
    }

    public void setRandomViolation(TrafficFineTable randomViolation) {
        this.randomViolation = randomViolation;
    }

    public TrafficFineTable getRandomViolation() {
        return randomViolation;
    }
}
