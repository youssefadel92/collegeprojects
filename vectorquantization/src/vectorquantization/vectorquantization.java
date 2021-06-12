package vectorquantization;

import java.awt.*;
import java.util.*;
import java.util.List;
import java.awt.image.BufferedImage;
import java.awt.image.WritableRaster;
import java.io.*;
import java.util.*;

import javax.imageio.*;

public class vectorquantization {
	
	 static int distance(List <Integer> x, List <Integer> y) {
	        int distance = 0;
	        for (int i = 0; i < x.size(); i++)
	        	distance +=Math.pow((x.get(i) - y.get(i)),2);
	            
	        return distance;
	    }
	
    private static List <Integer> constructhashmap(List<List<Integer>> codevectors, List<List<Integer>> quantized) {
    	
    	List <Integer> result = new ArrayList <Integer>();
    	
    	for (int i=0;i<codevectors.size();i++) {
    		
    		int min = 1000000000, index = -1, temp;
            for (int j =0; j < quantized.size(); j++) {
            	
            	temp = distance(codevectors.get(i), quantized.get(j));
            	
                if (temp < min) {
                    min = temp;
                    index = j;
                }
            }
            result.add(index);
    	}
        
        return result;
    }
	static List<Integer> getaverage(List<List<Integer>> codevectors) {
		
		List<Integer>average=new ArrayList<Integer> ();
		
		for(int i=0;i<codevectors.get(0).size();i++) {
			average.add(0);
		}// initialize vectors
		
		for(int i=0;i<codevectors.size();i++) {
			for(int j=0;j<codevectors.get(i).size();j++) {
				int temp=average.get(j)+codevectors.get(i).get(j);
				average.set(j, temp);
				
			}
		}// accumulate
		
		for(int i=0;i<average.size();i++) {
			int temp=average.get(i)/codevectors.size();
			average.set(i, temp);
		}// divide
           return average;
    }
    static int buildcodebook( List<List<Integer>> codevectors,int codebooksize, List<List<Integer>> quantizedcode) {
        if (codebooksize==1) {
            if (codevectors.size() > 0) {
            	quantizedcode.add(getaverage(codevectors));
            }
                
            return 0;//malhash lazma mogard betwa2f
        }
        
        List<List<Integer>> leftvectors=new ArrayList<List<Integer>> ();
        List<List<Integer>> rightvectors=new ArrayList<List<Integer>> ();
        
        List<Integer>average = getaverage(codevectors);
        
       
        
        for(int i=0;i<codevectors.size();i++) {
        	List<Integer> temp=codevectors.get(i);
        	
        	
        	
        	int dist = 0;
        	
            for (int j = 0; j < temp.size(); j++)//get distance with left
            {
            	
            	
            	dist += Math.pow((temp.get(j) - average.get(j)+1),2);
            	
            }
                
            int ldistance = (int) Math.sqrt(dist);;
            dist=0;
            
            for (int j = 0; j < temp.size(); j++)//get distance with right
            {
            	dist += Math.pow((temp.get(j) - average.get(j)-1),2);
            	//System.out.println("hello");
            }
                
            int rdistance = (int) Math.sqrt(dist);;
            
        	
            
            if (ldistance > rdistance) leftvectors.add(temp);
            else rightvectors.add(temp);
            
        	
        }
        //System.out.println(rightvectors.size());
        //System.out.println(leftvectors.size());
        buildcodebook(rightvectors, codebooksize /2, quantizedcode);
        buildcodebook(leftvectors, codebooksize /2, quantizedcode);
        return 0;
    }
	
    public static void writeImage(int[][] imagePixels, String outPath) {
        int height = imagePixels.length;
        int width = imagePixels[0].length;
        BufferedImage img = new BufferedImage(height, width, BufferedImage.TYPE_3BYTE_BGR);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int pixel = imagePixels[y][x];
                int fullrgb = (pixel) | (pixel << 16) | (pixel << 8) | pixel;

                img.setRGB(y, x, fullrgb);

            }
        }

        File f = new File(outPath);

        try {
            ImageIO.write(img, "jpg", f);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

public static void compress(String path,int height,int width, int number) {
	int imgwidth=0;
	int imgheight=0;

	File fil = new File(path); //image file path

    int[][] image = null;

    
        BufferedImage img;
		try {
			img = ImageIO.read(fil);
			imgwidth = img.getWidth();
	        imgheight = img.getHeight();

	        image = new int[imgwidth][imgheight];
	        
	        for (int y = 0; y < imgheight; y++) {
	            for (int x = 0; x < imgwidth; x++) {
	            	
	                int fullrgb = img.getRGB(x, y);
	                
	                int alpha = (fullrgb >> 24) & 0xff;
	                int red = (fullrgb >> 16) & 0xff;
	                int green = (fullrgb >> 8) & 0xff;
	                int blue = fullrgb & 0xff;
	                image[x][y] = (red+green+blue)/3;
	                
	                
	                
	            }
	        }
	        //writeImage(image,"C:\\Users\\test\\eclipse-workspace\\vectorquantization\\image.jpg");	        
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		/*--------------------*/

		int newwidth=imgwidth;
		int newheight=imgheight;
		int lastvalue=0;
		if ((imgheight) % height != 0) 
			newheight = ((imgheight / height) + 1) * height;
        if ((imgwidth) % width != 0) 
        	newwidth = ((imgwidth / width) + 1) * width;
        
        
        int[][] newimage = new int[newwidth][newheight];
        for (int y = 0; y < newheight; y++) {
        	for (int x = 0; x < newwidth; x++) {
                if (y+1>imgheight || x+1>imgwidth){
                    newimage[x][y] = lastvalue;
                    
                }
               else
               {
            	   
            	   newimage[x][y] = image[x][y];
            	   lastvalue = image[x][y];
               }
            }
        }
		
		
        //writeImage(newimage,"C:\\Users\\test\\eclipse-workspace\\vectorquantization\\image.jpg");
		
		/*--------------------*/
		
		/*--------------------*/
        
        List<List<Integer>> listcode = new ArrayList<List<Integer>> ();
        
        for (int i = 0; i < newheight; i += height)
            for (int j = 0; j < newwidth; j += width) {
            	List<Integer> temp=new ArrayList<Integer>();
                
                for (int x = i; x < i + height; x++)
                    for (int y = j; y < j + width; y++)
                        temp.add(newimage[y][x]); 
                listcode.add(temp);
            }

        /*
         * 1->2
         * 3->4
        */
       /* for(int i =0;i<listcode.size();i++){
        	List temp;
        	temp=listcode.get(i);
        	for(int j=0;j<temp.size();j++) {
        		System.out.println(temp.get(j));
        	}
        	System.out.println("--------------");
        }*/
        /*--------------------*/
        
        
        /*--------------------*/ //quantizing
        
        
        List<List<Integer>> quantizedcode = new ArrayList<List<Integer>> ();
        
        buildcodebook(listcode,number,quantizedcode);        // recursion because its a tree
        
        
        /*for(int i=0;i<quantizedcode.size();i++) {
        	System.out.println(quantizedcode.get(i));
        	System.out.println(i);
        }*/
        List<Integer> result=constructhashmap(listcode,quantizedcode);
        for(int i=0;i<result.size();i++) {
        	System.out.println(listcode.get(i));
        	
        	System.out.println(result.get(i));
        	System.out.println(quantizedcode.get(result.get(i)));
        	
        	System.out.println("------------");
        }        
        
    
        
        /*List<Integer> f=getaverage(listcode);
        for(int i =0;i<f.size();i++)
        {
        	System.out.println("ww");
        }*/
        
        
        /*--------------------*/
        
        /*--------------------*/
        
        FileOutputStream f;
		try {
			f = new FileOutputStream(new File("compressed.txt"));
			ObjectOutputStream o = new ObjectOutputStream(f);
			o.writeInt(newwidth);
			o.writeInt(newheight);
			o.writeInt(height);
			o.writeInt(width);
			o.writeObject(quantizedcode);
			o.writeObject(result);    
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		    
        
        /*--------------------*/
        
        
        

		
        
}
public static void decompress(String path) {
	FileInputStream fi;
	int newwidth=0,newheight=0,height=0,width=0;
	List<List<Integer>> quantizedcode=null;
	List<Integer> result=null;
	try {
		fi = new FileInputStream(new File(path));
		ObjectInputStream oi = new ObjectInputStream(fi);
		newwidth=oi.readInt();
		newheight=oi.readInt();
		height=oi.readInt();
		width=oi.readInt();
		quantizedcode=(List<List<Integer>>) oi.readObject();
		result=(List<Integer>) oi.readObject();
		
		
	} catch (FileNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	} catch (ClassNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	int[][] newImg2 = new int[newwidth][newheight];
    int ftemp=0;
    int v=0;
    for (int i = 0; i < newheight; i += height)
        for (int j = 0; j < newwidth; j += width) {
        	
            
            for (int x = i; x < i + height; x++) {
            	for (int y = j; y < j + width; y++) {
                	newImg2[y][x]=quantizedcode.get(result.get(ftemp)).get(v++);
                }
            }
                
            ftemp++;
            v=0;         
            
        }

    
    
    //Write image with Original Width/Height
    writeImage(newImg2,"C:\\Users\\test\\eclipse-workspace\\vectorquantization\\image.jpg");

	
	
	
	
	
}
	
	
	
	
	public static void main(String args[]) {
		
	    String path = "C:\\Users\\test\\eclipse-workspace\\vectorquantization\\017.jpg";
	    String path1 = "C:\\Users\\test\\eclipse-workspace\\vectorquantization\\compressed.txt";
		int height,width,number;
		Scanner input = new Scanner(System.in); // 2 2 64
        System.out.println("block height:");
        height = input.nextInt();
        System.out.println("block width:");
        width = input.nextInt();
        System.out.println("number of codebooks");
        number = input.nextInt();
        compress(path,height,width,number);
        System.out.println("conversion done");
        decompress(path1);
        
        
	}
}
