public class FindStringWithFor {
    public static void main(String[] args){
        String[] cities = {"New York", "Beijing", "Seoul"};
        boolean found = false; // Flag
        for (int i = 0; i<cities.length; i++){
            if (cities[i].equalsIgnoreCase("Seoul")) {
                System.out.printf("Index: %d, %s\n", i, cities[i]);
                found = true;
                break;
            }
        }
        if (found == false){
            System.out.println("Seoul not found");
        }
    }
}
