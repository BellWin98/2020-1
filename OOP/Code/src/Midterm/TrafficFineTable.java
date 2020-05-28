package Midterm;
/* Name: JongSeung Han
   Student ID: 201710736
 */
public enum TrafficFineTable {

    LIGHT(/*8*/9,/*7*/8,/*4*/5), PEDESTRIAN(8, 7, 5),
    YELLOW(10, 9, 0), BUSONLYHIGHWAY(10, 9, 0),
    LANE(4, 4, 3), OVER60(14, 13, 9),
    OVER4060(11, 10, 7), OVER2040(/*8*/12, /*7*/11, /*5*/8),
    OVER20(4, 4, 3);

    private int VAN;
    private int CAR;
    private int AUTO;

    TrafficFineTable(int VAN, int CAR, int AUTO) {
        this.VAN = VAN;
        this.CAR = CAR;
        this.AUTO = AUTO;
    }

    public int getVAN() {
        return VAN;
    }

    public int getCAR() {
        return CAR;
    }

    public int getAUTO() {
        return AUTO;
    }

}

