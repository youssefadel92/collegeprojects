package diskschedule;
import java.util.*;
import java.util.Scanner;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.math.*;

public class diskschedule {
	public static void main(String args[]) {
		int num=getsizeoffile();
		int n,start,total = 0,optimizedtotal;
		System.out.println("Choose an algorithm:\n1-FCFS\n2-SSTF\n3-SCAN\n4-C-SCAN\n5-C-Look\n");		
		Scanner in = new Scanner(System.in);
		n=in.nextInt();
		System.out.println("Enter the initial head start cylinder:");
		start=in.nextInt();
		int requests[]=new int[num];
		File file = new File("data.txt");
		Scanner scanner;
		try {
			scanner = new Scanner(file);
			int i=0;
			while(scanner.hasNextInt())
			{
			  requests[i]=scanner.nextInt();
			  i++;
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		in.close();
		
		if(n==1) {
			total=FCFS(requests,start);
		}
		else if(n==2) {
			total=SSTF(requests,start);
		}
		else if(n==3) {
			total=SCAN(requests,start);
		}
		else if(n==4) {
			total=CSCAN(requests,start);
		}
		else if(n==5) {
			total=CLOOK(requests,start);
		}
		System.out.println("------------------------------------");
		optimizedtotal=newoptimized(requests);
		System.out.println("------------------------------------");
		if(optimizedtotal<total) {
			System.out.println("Number of Total head movement in the new optimized algorithm is less than the choosen algorithm");
		}
		else
			System.out.println("Number of Total head movement in the new optimized algorithm is greater than the choosen algorithm");
		
		System.out.println("In this proposed algorithm, initially the disk head is at the\r\n" + 
				"position 0 and has the direction towards the position 200. It\r\n" + 
				"means initial head position and direction of head is always\r\n" + 
				"same. First we sort all the cylinders input blocks by using any\r\n" + 
				"sorting algorithm. Initially the head is at position 0 and\r\n" + 
				"sequentially moves and reached from this block to the highest\r\n" + 
				"input block number, servicing all the input request blocks in\r\n" + 
				"front of the head immediately.");

}

	private static int getsizeoffile() {
		// TODO Auto-generated method stub
		File file = new File("data.txt");
		String[] stringArray = null;
	    FileInputStream fis;
		try {
			fis = new FileInputStream(file);
		    byte[] byteArray = new byte[(int)file.length()];
		    fis.read(byteArray);
		    String data = new String(byteArray);
		    stringArray = data.split("\r\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return stringArray.length;

		
	}

	private static int newoptimized(int[] requests) {
		// TODO Auto-generated method stub
		PriorityQueue<Integer> queue = new PriorityQueue<Integer>();
		int start=0;
		int total = 0;
		for(int number:requests) {
				queue.add(number);	
		}
		while(true) {
			if(queue.size()==0) break;
			if(queue.size()==1) total=queue.peek();
			int temp=queue.poll();
			System.out.println(start+"->"+temp+" diff:"+(start-temp));
			
			start=temp;
		}
		System.out.println("Total head movemenet:"+total);
		return total;
		
	}

	private static int CLOOK(int[] requests, int start) {
		// TODO Auto-generated method stub
		PriorityQueue<Integer> queue = new PriorityQueue<Integer>();
		PriorityQueue<Integer> pqueue = new PriorityQueue<Integer>(); 
		int total=0;
		for(int number:requests) {
			if(number<start) {
				queue.add(number);	
			}
			else {
				pqueue.add(number);
			}
		}
		while(true) {
			if(pqueue.size()==0) break;
			
			int temp=pqueue.poll();
			System.out.println(start+"->"+temp+" diff:"+(start-temp));
			total+=Math.abs(start-temp);
			start=temp;
		}
		
		
		while(true) {
			if(queue.size()==0) break;
			int temp=queue.poll();
			System.out.println(start+"->"+temp+" diff:"+(start-temp));
			total+=Math.abs(start-temp);
			start=temp;
		}
		
		
		
		System.out.println("Total head movemenet:"+total);
		return total;
	}

	private static int CSCAN(int[] requests, int start) {
		// TODO Auto-generated method stub
		PriorityQueue<Integer> queue = new PriorityQueue<Integer>();
		PriorityQueue<Integer> pqueue = new PriorityQueue<Integer>(); 
		int total=0;
		for(int number:requests) {
			if(number<start) {
				queue.add(number);	
			}
			else {
				pqueue.add(number);
			}
		}
		pqueue.add(200);
		queue.add(0);
		while(true) {
			if(pqueue.size()==0) break;
			
			int temp=pqueue.poll();
			System.out.println(start+"->"+temp+" diff:"+(start-temp));
			total+=Math.abs(start-temp);
			start=temp;
		}
		
		while(true) {
			if(queue.size()==0) break;
			int temp=queue.poll();
			System.out.println(start+"->"+temp+" diff:"+(start-temp));
			total+=Math.abs(start-temp);
			start=temp;
		}
		
		
		
		System.out.println("Total head movemenet:"+total);
		return total;
	}

	private static int SCAN(int[] requests, int start) {
		// TODO Auto-generated method stub
		PriorityQueue<Integer> queue = new PriorityQueue<>(Collections.reverseOrder());
		PriorityQueue<Integer> pqueue = new PriorityQueue<Integer>(); 
		int total=0;
		for(int number:requests) {
			if(number<start) {
				queue.add(number);	
			}
			else {
				pqueue.add(number);
			}
		}
		queue.add(0);
		while(true) {
			if(queue.size()==0) break;
			int temp=queue.poll();
			System.out.println(start+"->"+temp+" diff:"+(start-temp));
			total+=Math.abs(start-temp);
			start=temp;
		}
		
		
		while(true) {
			if(pqueue.size()==0) break;
			
			int temp=pqueue.poll();
			System.out.println(start+"->"+temp+" diff:"+(start-temp));
			total+=Math.abs(start-temp);
			start=temp;
		}
		
		System.out.println("Total head movemenet:"+total);
		return total;
	}

	private static int SSTF(int[] requests, int start) {
		// TODO Auto-generated method stub
		int[] h = new int[requests.length];
	    System.arraycopy(requests, 0, h, 0, h.length);
		int total=0;
		while(true) {
			if(h.length==0) break;
			int index=findmin(h,start);
			int number=h[index];
			System.out.println(start+"->"+number);
			total+=Math.abs(start-number);
			start=number;
			h=removeelement(h,index);
		}
		System.out.println("Total head movemenet:"+total);
		return total;
	}



	private static int FCFS(int[] requests, int start) {
		// TODO Auto-generated method stub
		int total=0;
		for(int number: requests){
			System.out.println(start+"->"+number);
			total+=Math.abs(start-number);
			start=number;
		}
		System.out.println("Total head movemenet:"+total);
		return total;
		
	}
	
	private static int findmin(int[] h, int start) {
		// TODO Auto-generated method stub
		int diff = 100000;
		int index = -1;

		for(int i=0;i<h.length;i++) {
			if(Math.abs(h[i]-start)<diff&&h[i]!=start) {
				diff=Math.abs(h[i]-start);
				index=i;
			}
		}

		return index;
	}

	private static int[] removeelement(int[] arr, int index) {
		// TODO Auto-generated method stub
		if (arr == null
	            || index < 0
	            || index >= arr.length) { 
	  
	            return arr; 
	        } 
	  
	        // Create another array of size one less 
	        int[] anotherArray = new int[arr.length - 1]; 
	  
	        // Copy the elements except the index 
	        // from original array to the other array 
	        for (int i = 0, k = 0; i < arr.length; i++) { 
	  
	            // if the index is 
	            // the removal element index 
	            if (i == index) { 
	                continue; 
	            } 
	  
	            // if the index is not 
	            // the removal element index 
	            anotherArray[k++] = arr[i]; 
	        } 
	  
	        // return the resultant array 
	        return anotherArray; 
	}
	
	
}
