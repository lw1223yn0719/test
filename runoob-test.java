package code;
import java.util.Scanner;

public class maxNU {
	public  void main(String[] args) {
		Scanner inport=new Scanner(System.in);
		int i,n;
		int[] num=new int[100];
		n=inport.nextInt();
		for(i=0;i<n;i++)
			num[i]=inport.nextInt();
		int result = sum(num);
        System.out.println("连续子元素的最大和为："+result);
		inport.close();
	}
		public int sum(int[] num) {
			if (num.length==0 || num==null) {
				return 0;
			}
			int currentSum = 0;     
			int max = 0;           
			for (int i = 0; i <num.length; i++) {
				if(currentSum<=0){     
					currentSum = num[i];     
				}else{
					currentSum = currentSum + num[i];   
				}
				if(currentSum>max){         
					max = currentSum;      
				}
			}
			return max;
		} 
}