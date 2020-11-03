import java.beans.ExceptionListener;
import java.beans.XMLDecoder;
import java.beans.XMLEncoder;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
 
public class XmlEncoder{
	private static void serializeToXML (UserSettings settings) throws IOException
	{
   	FileOutputStream fos = new FileOutputStream("settings.xml");
    	XMLEncoder encoder = new XMLEncoder(fos);
    	encoder.setExceptionListener(new ExceptionListener() {
            public void exceptionThrown(Exception e) {
                System.out.println("Exception! :"+e.toString());
            }
    	});
    	encoder.writeObject(settings);
    	encoder.close();
    	fos.close();
	}

	public static void main(String args[]) throws IOException{
	UserSettings myobj=new UserSettings();
	myobj.setFieldOne(11000);
        myobj.setFieldTwo("Khuch din to gujarat mein");
        myobj.setFieldThree(true);
	serializeToXML(myobj);
	}
	
}

