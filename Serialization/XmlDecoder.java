import java.beans.ExceptionListener;
import java.beans.XMLDecoder;
import java.beans.XMLEncoder;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class XmlDecoder{
	private static UserSettings deserializeFromXML() throws IOException {
    		FileInputStream fis = new FileInputStream("settings.xml");
    		XMLDecoder decoder = new XMLDecoder(fis);
    		UserSettings decodedSettings = (UserSettings) decoder.readObject();
    		decoder.close();
    		fis.close();
    		return decodedSettings;
	}
	public static void main(String args[]) throws IOException{
		UserSettings myobj=new UserSettings();
		myobj=deserializeFromXML();
		System.out.println(myobj);
		//deserializeFromXML();
			
	}
}
