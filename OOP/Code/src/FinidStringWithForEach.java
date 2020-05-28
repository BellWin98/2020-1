public class FinidStringWithForEach {
    public static void main(String[] args){
        String[] cities = {"New York", "Beijing", "Seoul"};
        boolean found = false; // Flag
        int index = 0;
        for (String city:cities){
            if (city.equalsIgnoreCase("Seoul")) {
                System.out.printf("Index: %d, %s\n", index, cities[index]);
                found = true;
                break;
            }
            index++;
        }
        if (found == false){
            System.out.println("Seoul not found");
        }
    }
}
