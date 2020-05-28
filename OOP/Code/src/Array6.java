public class Array6 {
    public static void main(String[] args){
        // 배열 선언의 두가지 방법.
        // 들여쓰기 단축키: Shift+Tab
        double[] arr = {1.1,2.3,4.7,7.5};
        System.out.printf("Length: %d\n", arr.length);
        for (int i = 0; i<arr.length; i++) {
            System.out.printf("arr[%d] = %.1f\n", i, arr[i]);
        }

        double[] arr1 = new double[4];
        arr1[0] = 1.1;
        arr1[1] = 2.2;
        arr1[2] = 3.3;
        arr1[3] = 4.4;

        for (int j = 0; j<arr1.length; j++){
            System.out.printf("arr1[%d] = %.1f\n", j, arr1[j]);
        }
    }
}
