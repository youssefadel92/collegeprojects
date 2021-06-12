package URl;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.RandomAccessFile;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.Socket;



public class Download extends Thread{
	boolean paused=false;
	String FileName;
	String link;
	int Num;
	String Location;
	int downloaded=0;
	double downloadedpercentage=0.00;
	long filesize;
	URL url;
	int status;  //0=paused--1=downloading
	long startbyte,endbyte;
	private static int MAX_BUFFER_SIZE = 1024;
	public Download(String x,String y,long g,long f) {
		status=1;
		link=x;
		Location=y;
		startbyte=g;
		endbyte=f;
		
		try {
			url=new URL(link);
			Socket socket;
			String path=url.getPath();
			String domain=url.getHost();
			socket = new Socket(domain,80);
			PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())));
	        out.println("GET "+path+" HTTP/1.1\n" +"Host: "+domain);
	        out.println();
	        out.flush();
	        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String inputLine;
            int g1=0;
            while ((inputLine = in.readLine()) != null && inputLine.trim() != "0"&&g1<30) {
            	if (inputLine.length()>14&&inputLine.substring(0,14).equals("Content-Length")) {
            		filesize=Long.parseLong(inputLine.substring(16));
            		break;
            	}
            	g1++;
            }
            socket.close();
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Location+=url.getFile().substring(url.getFile().lastIndexOf('/')+1);
		
	}
	public void createfile() {
		File out;
		out=new File(Location);	
	}
	/*public void rundownload(long x,long y) {
		
        Thread thread = new Thread(this);
        thread.run();
    }*/
	public void pause() {
        status = 0;
        paused=true;
    }
	public void Resume() {
        status = 1;
    }
	
	
	@Override
	public void run() {
		try {
			RandomAccessFile file = null;
			String path=url.getPath();
			String domain=url.getHost();
			
			Socket socket = new Socket(domain,80);
			PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())));
	        out.println("GET "+path+" HTTP/1.1\n" +"Host: "+domain+"\nRange: bytes="+startbyte+"-"+endbyte);
	        out.println();
	        out.flush();
			BufferedInputStream inputStream= new BufferedInputStream(socket.getInputStream());
			file = new RandomAccessFile(Location, "rw");
		    file.seek(startbyte);
		    boolean headerEnded = false;
            boolean stat = true;
            byte[] buffer = new byte[MAX_BUFFER_SIZE];//1024
            int length = 0;
            while (stat&&status==1) {
            	if(inputStream.available()>0) {
            		length=inputStream.read(buffer,0, MAX_BUFFER_SIZE);
            		System.out.println(length);
            	}
            	else
            		break;
            		//System.out.println(length);
            	if(length==-1) {
            		stat=false;
            		break;
            	}
            	if(length==0) {
            		
            		System.out.println("Read Is 0");
            	}
            	else System.out.println("Length is "+length);
            	
            	/*
            	for (int i = 0; i < length-4; i++) {
                    if (buffer[i] == 37 && buffer[i + 1] == 37 && buffer[i + 2] == 69 && buffer[i + 3] == 79 && buffer[i + 4] == 70 ) {
                        stat = false;
                    }
                }*/
            	
                // If the end of the header had already been reached, write the bytes to the file as normal.
                if (headerEnded) {
                	file.write(buffer,0,length);
                	downloaded+=length;
                	downloadedpercentage=(downloaded*100.0)/filesize;
                	
                }
                // the HTTP header end "\r\n\r\n" (integer representation 13 10 13 10).
                else {
                    for (int i = 0; i < length-3; i++) {
                        if (buffer[i] == 13 && buffer[i + 1] == 10 && buffer[i + 2] == 13 && buffer[i + 3] == 10) {
                            headerEnded = true;
                            file.write(buffer, i+4 , MAX_BUFFER_SIZE-i-4);
                            break;
                        }
                    }
                }
                
                System.out.println(downloadedpercentage);
                
            }
		    System.out.println("Download Completed");
			inputStream.close();
			file.close();
			socket.close();
			
			
			
		}
		catch(IOException error) {
			error.printStackTrace();
		}

	}
	
}
