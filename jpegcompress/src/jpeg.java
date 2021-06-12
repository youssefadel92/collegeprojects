import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.filechooser.FileSystemView;

import javax.swing.JButton;
import javax.swing.JFileChooser;

import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Vector;
import java.awt.event.ActionEvent;

public class jpeg {

	
	private static String path;
	static Vector<Integer> orignaldata = new Vector<Integer>();
	//
	static List<Node> orignaltags = new ArrayList<Node> ();
	
	
	private static Map<Node, String> huffmancode = new HashMap<Node,String>(); //huffmancode
	private static Map<String, Node> huffmancodes = new HashMap<String,Node>(); //huffmancode
	
	
	static int ProbOfOthers = 0;
	static String others = "";
	
	
	public static int categoryvalue(int x) {
        String temp = Integer.toBinaryString(x);
        return temp.length();
    }
	public static String reverse(String x) {
		
		String result = "";
        for (int i = 0; i < x.length(); i++) {
            if (x.charAt(i) == '1') {
                result += '0';
            } else if (x.charAt(i) == '0') {
                result += '1';
            }
        }
        return result;
		
		
	}
	public static int findinmap(List<Node> x,int zero,int category) {
		Node temp;
		for(int i=0;i<x.size();i++) {
			temp=x.get(i);
			
			if(temp.category==category&&temp.zerocount==zero) {
				return i;
			}
		}
		return -1;
		
	}

	public static void compresscode(){
		
		///////////////////////////////////////////// readfile
		String temp = ""; 
        BufferedReader br;
		try {
			br = new BufferedReader(new FileReader(path));
			temp = br.readLine();
			
	        br.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        String[] parts = temp.split(",");
        for (int i = 0; i < parts.length; i++) {
        	
            int x = Integer.parseInt(parts[i].trim());
            orignaldata.addElement(x);
        }
		///////////////////////////////////////////
        int zerocount = 0;
        
        for (int i = 0; i < orignaldata.size(); i++) {
        	if(i==orignaldata.size()-1) {
            	
            	Node x=new Node();
        		x.left=null;
        		x.right=null;
        		x.category=-1;
        		x.zerocount=-1;
        		x.eob="eob";
        		x.data=1;
        		
        		orignaltags.add(x);
            }else if(orignaldata.get(i)==0) {
            	zerocount++;
            	continue;
            }
            
            else
            {
            	if(findinmap(orignaltags,zerocount,categoryvalue(Math.abs(orignaldata.get(i))))==-1) {
            		Node x=new Node();
            		x.left=null;
            		x.right=null;
            		x.category=categoryvalue(Math.abs(orignaldata.get(i)));
            		x.zerocount=zerocount;
            		x.data=1;
            		
            		zerocount=0;
            		orignaltags.add(x);
            		
            	}
            	else{
            		
            		int pos=findinmap(orignaltags,zerocount,categoryvalue(Math.abs(orignaldata.get(i))));
            		
            		orignaltags.get(pos).data++;
            		
            		zerocount=0;
            		
            	}
            	
            	
            	
            }
        }
        
        
/*        
        int tempprob=0;
        for (int i = 0; i < orignaltags.size(); i++) {
        	tempprob+= orignaltags.get(i).data;
        	
        }
        for (int i = 0; i < orignaltags.size(); i++) {
        	 orignaltags.get(i).data/=tempprob;
        	 
         }*/
		/*for(int i=0;i<orignaltags.size();i++) {
			System.out.print(orignaltags.get(i).zerocount+"/");
			System.out.print(orignaltags.get(i).category+" ");
			System.out.println(orignaltags.get(i).data);
			
		}*/
		
		
		PriorityQueue<Node> Q = new PriorityQueue<Node>(orignaltags.size(), new comparator());
		for(int i=0;i<orignaltags.size();i++) {
			Q.add(orignaltags.get(i));
		}
		Node root = null;
		while (Q.size() > 1) { 
		  	  
	        Node x = Q.poll(); //small
	        

	        Node y = Q.poll(); //smallest

	        Node NN = new Node();  
	        NN.data = x.data + y.data; 
	        
	        NN.left = x; 
	        NN.right = y;  
	        root = NN;  
	        Q.add(NN); 
	    } 
		printCode(root,"");
		
	/*	for(int i=0;i<orignaltags.size();i++) {
			System.out.print(orignaltags.get(i).zerocount+"/");
			System.out.print(orignaltags.get(i).category+" ");
			System.out.print(orignaltags.get(i).data+"  ");
			
			System.out.println(":" + huffmancode.get(orignaltags.get(i)));
			
	        
		}
		*/
		
		
		try {
			FileWriter f;
			FileWriter f1;
			f = new FileWriter("result.txt");
			BufferedWriter bf = new BufferedWriter(f);
			f1 = new FileWriter("huffman.txt");
			BufferedWriter bf1 = new BufferedWriter(f1);
			int zeros = 0;
	        for (int i = 0; i < orignaldata.size(); i++) {
	        	if(orignaldata.get(i)==0) {
	        		zeros++;
	        		continue;
	        	}
	        	else
	        	{
	        		
	        		int pos= findinmap(orignaltags,zeros,categoryvalue(Math.abs(orignaldata.get(i))));
	        		Node tempnode=orignaltags.get(pos);
	        		
	        		String binary = Integer.toBinaryString(Math.abs(orignaldata.get(i)));
	        		
	                if (orignaldata.get(i) < 0) {
	                    binary = reverse(binary);
	                }
	        		bf.write(huffmancode.get(tempnode)+",");
	        		bf.write(binary+" ");
	        		
	        		zeros=0;
	        		
	        	}
	            
	        }
	        bf.write("eob");
			bf.close();
			
			for(int i=0;i<orignaltags.size();i++) {
				bf1.write(orignaltags.get(i).zerocount+"/");
				bf1.write(orignaltags.get(i).category+" ");
				bf1.write(huffmancode.get(orignaltags.get(i)));
				bf1.newLine();
			}
			
			bf1.close();
	        
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
      
		
		
		
		
		
		
		
				
        }
        
        
        
  
 public static void decompress() {
	 /*--------------------------*/
		
		
     
     try {
     	String line;
         BufferedReader reader = new BufferedReader(new FileReader("huffman.txt"));
			while ((line = reader.readLine()) != null) {
			    String[] tempparts = line.split(" ");
			    String key = tempparts[0], code = tempparts[1];
			    Integer zerooos = -1, ctval = -1;
			    
			        key = "";
			        String symbol = tempparts[0];
			        String[] newparts = symbol.split("\\/");
			        zerooos = Integer.parseInt(newparts[0]);
			        ctval = Integer.parseInt(newparts[1]);
			        Node temnode=new Node();
			        temnode.zerocount=zerooos;
			        temnode.category=ctval;
			        
			        huffmancodes.put(code, temnode);
			}
			reader.close();
			        
			        
			        
			        

			        
			        reader = new BufferedReader(new FileReader("result.txt"));
			      
			        String encoded = reader.readLine();
			        reader.close();
			        String result="";
			        
			        String[] splited=encoded.split(" ");
			        for(int i=0;i<splited.length-1;i++) {
			        	String splitofsplit[]=splited[i].split(",");
			        	String Zeroes="";
			        	for(int j=0;j<huffmancodes.get(splitofsplit[0]).zerocount;j++) {
			        		Zeroes+="0,";
			        	}
			        	
			        	boolean flag = false;
			            if (splitofsplit[1].charAt(0) == '0') {//negative
			            	splitofsplit[1] = reverse(splitofsplit[1]);
			                flag = true;
			            }
			            int x = Integer.parseInt(splitofsplit[1], 2);
			            if (flag == true) {
			                x = Math.negateExact(x);//make it negative
			            }
			            String y = Integer.toString(x);
			            //System.out.print(Zeroes);
			        	//System.out.print(y+",");
			            result+=Zeroes;
			            result+=y;
			            result+=",";
			        }
			        
			        
			        FileWriter f = new FileWriter("decompressed.txt");
			        BufferedWriter bf = new BufferedWriter(f);
			        bf.write(result);
			        bf.close();
			        
			                
			        
			        
			
		} catch (NumberFormatException | IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
		
		/*--------------------------*/
		
		
		
		
 }
		
		
		
	
	
	
	
	 public static void printCode(Node root, String s) 
	    { 
	  
	        // base case
	        if (root.left == null&& root.right == null) { 
	        	
	            huffmancode.put(root, s);
	            
	  
	            return; 
	        } 
	        printCode(root.left, s + "1"); 
	        printCode(root.right, s + "0"); 
	    } 

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	private JFrame frame;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					jpeg window = new jpeg();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public jpeg() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 414, 125);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		JButton btnNewButton = new JButton("Load");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JFileChooser j = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory()); 

 
                int r = j.showOpenDialog(null); 
                if (r == JFileChooser.APPROVE_OPTION) 

                { 
 
                    path=j.getSelectedFile().getAbsolutePath();
                    System.out.println(path);
                } 
 
                else
                    path=null;
                
                
			}
		});
		btnNewButton.setBounds(22, 24, 111, 38);
		frame.getContentPane().add(btnNewButton);
		
		JButton btnCompress = new JButton("Compress");
		btnCompress.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				compresscode();
		        
			}
		});
		btnCompress.setBounds(143, 24, 111, 38);
		frame.getContentPane().add(btnCompress);
		
		JButton btnDecompress = new JButton("Decompress");
		btnDecompress.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				decompress();                               
			}
		});
		btnDecompress.setBounds(264, 24, 111, 38);
		frame.getContentPane().add(btnDecompress);
	}
}
