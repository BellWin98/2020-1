public class Output10_59 {
    public static void main(String[] args) {
//        for (int i = 10; i<=50; i+=10){
//            for (int j =0; j<=9; j++){
//                System.out.print(""+ i+j);
//                System.out.print(" ");
//            }
//        }
//    }
//
        for (int i = 10; i <= 50; i += 10) {
            int j = 0;
            while (j <= 9) {
                System.out.print(i + j);
                System.out.print(" ");
                j++;
            }
        }
    }
}