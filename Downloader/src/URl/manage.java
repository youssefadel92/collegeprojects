

//package URl;
// this class is not used i got links in it for testing
/*public class manage {
	public static void downloadsss(String args[]) throws InterruptedException {
		//Download Z=new Download("https://f9.file-upload.com:183/d/ruxltiwwnlgpv7w7ww2ygq2nz42sy2jsr6fuaxi6ujva6e7gbv3u2dkum4rutmiznwhdmpw3/Fantastic.Beasts.The.Crimes.Of.Grindelwald.2018.EXTENDED.BluRay.MyEgy.1080p.mp4","D:\\Files\\lectures\\",1);
		//Z.rundownload();
		Thread.sleep(18000);
		//Z.pause();
		Thread.sleep(9000);
		//Z.resume();
		
	}
}*/
/* testing links*/
/*---------------------------------------------------------------------*/
//http://www.ncert.nic.in/NCERTS/l/jemh1an.pdf
//http://www.peoplelikeus.org/piccies/codpaste/codpaste-teachingpack.pdf
/*---------------------------------------------------------------------*/
/*

try {
			String path=url.getPath();
			String domain=url.getHost();
			System.out.println(path);
			System.out.println(domain);
			Socket socket = new Socket(domain,80);
			PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())));
	        out.println("GET "+path+" HTTP/1.1\n" +"Host: "+domain+"\nRange: bytes="+startbyte+"-"+endbyte);
	        out.println();
	        out.flush();
            //BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            //String inputLine;
            //int g=0;
            //while ((inputLine = in.readLine()) != null && inputLine.trim() != "0"&&g<20) {
              // System.out.println(inputLine);
               //g++;
            //}
            final FileOutputStream fileOutputStream = new FileOutputStream(Location);
            BufferedInputStream inputStream = new BufferedInputStream(socket.getInputStream());
            // Header end flag.
            boolean headerEnded = false;
            boolean stat = true;
            byte[] bytes = new byte[1024];
            int length = 0;
            while (stat) {
            	length=inputStream.read(bytes,0, 1024);
            	//System.out.println(length);
                // If the end of the header had already been reached, write the bytes to the file as normal.
                if (headerEnded) {
                	for (int i = 0; i < 1020; i++) {
                        if (bytes[i] == 37 && bytes[i + 1] == 37 && bytes[i + 2] == 69 && bytes[i + 3] == 79 &&bytes[i + 4] == 70) {
                            fileOutputStream.write(bytes, 0 , i);
                            stat=false;
                            //length=inputStream.read(bytes,0, 1);
                            //System.out.println(length+"ss");
                            break;
                        }
                    }
                	if(stat==true)fileOutputStream.write(bytes, 0 , length);
                
                }
                // This locates the end of the header by comparing the current byte as well as the next 3 bytes
                // with the HTTP header end "\r\n\r\n" (which in integer representation would be 13 10 13 10).
                // If the end of the header is reached, the flag is set to true and the remaining data in the
                // currently buffered byte array is written into the file.
                else {
                    for (int i = 0; i < length-3; i++) {
                        if (bytes[i] == 13 && bytes[i + 1] == 10 && bytes[i + 2] == 13 && bytes[i + 3] == 10) {
                            headerEnded = true;
                            fileOutputStream.write(bytes, i+4 , 1024-i-4);
                            break;
                        }
                    }
                }
            }
            System.out.println("done");
            inputStream.close();
            fileOutputStream.close();
            socket.close();
           
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
*/