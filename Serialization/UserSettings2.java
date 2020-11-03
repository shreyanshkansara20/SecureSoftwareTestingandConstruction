public class UserSettings2 {

	static{
		System.out.println("Static called!");
	}

	//static UserSettings2(){
	//	System.out.println("Static Constructor Called");	
	//	}
     
    public UserSettings2(){
	System.out.println("hello");
	}


     
    private Integer fieldOne;
    private String fieldTwo;
    private boolean fieldThree;
 
    public Integer getFieldOne() {
        return fieldOne;
    }
 
    public void setFieldOne(Integer fieldOne) {
        this.fieldOne = fieldOne;
    }
 
    public String getFieldTwo() {
        return fieldTwo;
    }
 
    public void setFieldTwo(String fieldTwo) {
        this.fieldTwo = fieldTwo;
    }
 
    public boolean isFieldThree() {
        return fieldThree;
    }
 
    public void setFieldThree(boolean fieldThree) {
        this.fieldThree = fieldThree;
    }
		
 
    @Override
    public String toString() {
        return "UserSettings [fieldOne=" + fieldOne + ", fieldTwo=" + fieldTwo
                + ", fieldThree=" + fieldThree + "]";
    }
}
