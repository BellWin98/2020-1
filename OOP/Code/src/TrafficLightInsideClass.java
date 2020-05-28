public class TrafficLightInsideClass {
    enum TrafficLight {
        RED(30), AMBER(10), GREEN(30);
        int seconds;
        TrafficLight(int seconds){
            this.seconds = seconds;
        }
        int getSeconds() {
            return seconds;
        }
    }
    public static void main(String[] args){
        for (TrafficLight light: TrafficLight.values()) {
            System.out.printf("%s blinks for %d\n", light, light.getSeconds());
        }
    }
}


