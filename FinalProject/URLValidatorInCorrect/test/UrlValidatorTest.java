

import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

// Source cited: how to pick a random element from an array in Java 
// https://stackoverflow.com/questions/8065532/how-to-randomly-pick-an-element-from-an-array

Random generator = new Random();
   
public String randomSelect(String[] array) {
	      int random_index = generator.nextInt(array.length);
	      return array[random_index];
	   }
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	

-	 //UrlValidator urlValidator2 = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
-     String[] schemes = {"http","https", "files", "ftp"};
-     //UrlValidator urlValidator2 = new UrlValidator(schemes);
-     UrlValidator urlValidator2 = new UrlValidator(schemes, UrlValidator.NO_FRAGMENTS);
-     
-     String[] validUrls = {"http://www.toga.com:21", "https://www.amazon.com/80", "ftp://dropbox.com", "https://www.google.com/"};
-     String[] invalidUrls = {"https://www.amazon.com:80000", "ftp:://foo.bar.com/", "dog...dog", "tim.jones.com"};
-     
-     for (int i = 0; i < invalidUrls.length; i++) {
-	       
-    	 //System.out.println((urlValidator2.isValid(invalidUrls[i])));
-		 assertFalse(urlValidator2.isValid(invalidUrls[i]));
-	 }
-	 	
-     
-     for (int i = 0; i < validUrls.length; i++) {
-       
-    	 	assertTrue(urlValidator2.isValid(validUrls[i]));
-    	    //System.out.println((urlValidator2.isValid(validUrls[i])));
-     }      
	   
   }
   
   // valid URLs
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   
	   int NUM_TESTS_1 = 100;
	   // valid string arrays to build valid URL
	   String[] validSchemes = new String[] {"http://", "ftp://", "https://"};
	   String[] validAuthorities = new String[] {"www.amazon.com", "amazon.au", "255.255.255.255"};
	   String[] validPorts = new String[] {":80", ":65555", ":0", ""};
	   String[] validPaths = new String[] {"/test", "/564543", "/test/", "", "/test/file", "test/file/path"};
	   String[] queries = new String[] {"", "?action=view"};

	   UrlValidator urlVal1 = new UrlValidator();

	   System.out.println();
	   System.out.println();
	   System.out.println(">> Start testing valid URLs partition...");
	   System.out.println();
	   System.out.println();
	   for (int i = 0; i < NUM_TESTS_1; i++) {
	       String Scheme1 = randomSelect(validSchemes);
	       String Authority1 = randomSelect(validAuthorities);
	       String Ports1 = randomSelect(validPorts);
	       String Paths1 = randomSelect(validPaths);
	       String Query1 = randomSelect(queries); 
	       
	       // build a full URL to test from random selections
	       String URL = Scheme1 + Authority1 + Ports1 + Paths1 + Query1;
	       System.out.println(URL + "  is under test.");
	       assertTrue(URL, urlVal1.isValid(URL)); 
	   }  
	   System.out.println();
	   System.out.println();
	   System.out.println(">> Finished testing valid URLs partition...NO ERRORS DETECTED!!!"); 
	   System.out.println();
	   System.out.println();
   }
   
   //invalid URLs
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	
	   int NUM_TESTS_2 = 100;  
	   // invalid string arrays to build invalid URL  
	   String[] invalidSchemes = new String[] {"3ht://", "http:/", "http/", "://", "", "h3t://"};
	   String[] invalidAuthorities = new String[] {"amazon.qwertyuiop234", "", "aaa", "1.2.3.4.5"};
	   String[] invalidPorts = new String[] {":asdflkj", "800000000", ":-5", ":-501"};
	   String[] invalidPaths = new String[] {"//test", "/test//file", "/.../", "///..///"};
	   String[] queries = new String[] {"", "?action=view"};
	   
	   UrlValidator urlVal2 = new UrlValidator();
	   System.out.println();
	   System.out.println();
	   System.out.println(">> Start testing invalid URLs partition...");
	   System.out.println();
	   System.out.println();

	   for (int i = 0; i < NUM_TESTS_2; i++) {
	       String Scheme2 = randomSelect(invalidSchemes);
	       String Authority2 = randomSelect(invalidAuthorities);
	       String Ports2 = randomSelect(invalidPorts);
	       String Paths2 = randomSelect(invalidPaths);
	       String Query2 = randomSelect(queries);
	     

	       // build a full invalid URL to test from random selections  
	       String URL = Scheme2 + Authority2 + Ports2 + Paths2 + Query2;
	       System.out.println(URL + "  is under test.");
	       assertFalse(URL, urlVal2.isValid(URL));

	   }
	   System.out.println();
	   System.out.println();
	   System.out.println(">> Finished testing invalid URLs partition...NO ERRORS DETECTED!!!"); 
	   System.out.println();
	   System.out.println();
 }

   // valid URLS without Port 
   public void testYourThirdPartition() {
   
	   int NUM_TESTS_3 = 100;
	   String[] validSchemes = new String[] {"https://", "ftp://", "http://"};
	   String[] validAuthorities = new String[] {"www.google.com", "google.ca", "255.255.255.255"};
	   // String[] validPorts = new String[] {":80", ":65555", ":0", ""};
	   String[] validPaths = new String[] {"/test", "/564543", "/test/", "", "/test/file", "test/file/path"};
	   String[] queries = new String[] {"", "?action=go", "?Search=new"};
	   
	   UrlValidator urlVal3 = new UrlValidator();

	   System.out.println();
	   System.out.println();
	   System.out.println(">> Start testing valid URLs partition WITHOUT ports...");
	   System.out.println();
	   System.out.println();
	   for (int i = 0; i < NUM_TESTS_3; i++) {
	       String Scheme3 = randomSelect(validSchemes);
	       String Authority3 = randomSelect(validAuthorities);
	       // String Ports1 = randomSelect(validPorts);
	       String Paths3 = randomSelect(validPaths);
	       String Query3 = randomSelect(queries); 
	       
	       // build a full URL to test from random selections
	       String URL = Scheme3 + Authority3 + Paths3 + Query3;
	       System.out.println(URL + "  is under test.");
	       assertTrue(URL, urlVal3.isValid(URL)); 
	   }  
	   System.out.println();
	   System.out.println();
	   System.out.println(">> Finished testing valid URLs partition WITHOUT ports...NO ERRORS DETECTED!!!"); 
	   System.out.println();
	   System.out.println();
   }
    
   // valid URLS without Port and without Queries 
   public void testYourFourthPartition() {
   
	   int NUM_TESTS_4 = 100;
	   String[] validSchemes = new String[] {"https://", "ftp://", "http://"};
	   String[] validAuthorities = new String[] {"www.google.com", "google.ca", "255.255.255.255"};
	   // String[] validPorts = new String[] {":80", ":65555", ":0", ""};
	   String[] validPaths = new String[] {"/test", "/564543", "/test/", "", "/test/file", "test/file/path"};
	  // String[] queries = new String[] {"", "?action=go", "?Search=new"};
	   
	   UrlValidator urlVal4 = new UrlValidator();

	   System.out.println();
	   System.out.println();
	   System.out.println(">> Start testing valid URLs partition WITHOUT queries+ports...");
	   System.out.println();
	   System.out.println();
	   for (int i = 0; i < NUM_TESTS_4; i++) {
	       String Scheme4 = randomSelect(validSchemes);
	       String Authority4 = randomSelect(validAuthorities);
	       // String Ports1 = randomSelect(validPorts);
	       String Paths4 = randomSelect(validPaths);
	       // String Query3 = randomSelect(queries); 
	       
	       // build a full URL to test from random selections
	       String URL = Scheme4 + Authority4 + Paths4;
	       System.out.println(URL + "  is under test.");
	       assertTrue(URL, urlVal4.isValid(URL)); 
	   }  
	   System.out.println();
	   System.out.println();
	   System.out.println(">> Finished testing valid URLs partition WITHOUT queries+ports...NO ERRORS DETECTED!!!"); 
	   System.out.println();
	   System.out.println();
   }
   
   // valid URLS without Port+Queries+Paths 
   public void testYourFifthPartition() {
   
	   int NUM_TESTS_5 = 100;
	   String[] validSchemes = new String[] {"https://", "ftp://", "http://"};
	   String[] validAuthorities = new String[] {"www.google.com", "google.ca", "255.255.255.255"};
	   // String[] validPorts = new String[] {":80", ":65555", ":0", ""};
	  // String[] validPaths = new String[] {"/test", "/564543", "/test/", "", "/test/file", "test/file/path"};
	  // String[] queries = new String[] {"", "?action=go", "?Search=new"};
	   
	   UrlValidator urlVal5 = new UrlValidator();

	   System.out.println();
	   System.out.println();
	   System.out.println(">> Start testing valid URLs partition WITHOUT queries+ports+paths...");
	   System.out.println();
	   System.out.println();
	   for (int i = 0; i < NUM_TESTS_5; i++) {
	       String Scheme5 = randomSelect(validSchemes);
	       String Authority5 = randomSelect(validAuthorities);
	       // String Ports1 = randomSelect(validPorts);
	       // String Paths4 = randomSelect(validPaths);
	       // String Query3 = randomSelect(queries); 
	       
	       // build a full URL to test from random selections
	       String URL = Scheme5 + Authority5;
	       System.out.println(URL + "  is under test.");
	       assertTrue(URL, urlVal5.isValid(URL)); 
	   }  
	   System.out.println();
	   System.out.println();
	   System.out.println(">> Finished testing valid URLs partition WITHOUT queries+ports+paths...NO ERRORS DETECTED!!!"); 
	   System.out.println();
	   System.out.println();
   }
   
   // valid URLS http:// only 
   public void testYourSixthPartition() {
   
	   int NUM_TESTS_6 = 100;
	   String[] validSchemes = new String[] {"http://"};
	   String[] validAuthorities = new String[] {"www.yahoo.com", "google.ca", "255.255.255.255"};
	   // String[] validPorts = new String[] {":80", ":65555", ":0", ""};
	  // String[] validPaths = new String[] {"/test", "/564543", "/test/", "", "/test/file", "test/file/path"};
	  // String[] queries = new String[] {"", "?action=go", "?Search=new"};
	   
	   UrlValidator urlVal6 = new UrlValidator();

	   System.out.println();
	   System.out.println();
	   System.out.println(">> Start testing valid URLs partition (http only) WITHOUT queries+ports+paths...");
	   System.out.println();
	   System.out.println();
	   for (int i = 0; i < NUM_TESTS_6; i++) {
	       String Scheme6 = randomSelect(validSchemes);
	       String Authority6 = randomSelect(validAuthorities);
	       // String Ports1 = randomSelect(validPorts);
	       // String Paths4 = randomSelect(validPaths);
	       // String Query3 = randomSelect(queries); 
	       
	       // build a full URL to test from random selections
	       String URL = Scheme6 + Authority6;
	       System.out.println(URL + "  is under test.");
	       assertTrue(URL, urlVal6.isValid(URL)); 
	   }  
	   System.out.println();
	   System.out.println();
	   System.out.println(">> Finished testing valid URLs partition (https only) WITHOUT queries+ports+paths...NO ERRORS DETECTED!!!"); 
	   System.out.println();
	   System.out.println();
   }
   
   
// valid authority only 
   public void testYourSeventhPartition() {
   
	   int NUM_TESTS_7 = 100;
	   // String[] validSchemes = new String[] {"https://"};
	   String[] validAuthorities = new String[] {"www.yahoo.com", "google.ca", "255.255.255.255"};
	   // String[] validPorts = new String[] {":80", ":65555", ":0", ""};
	  // String[] validPaths = new String[] {"/test", "/564543", "/test/", "", "/test/file", "test/file/path"};
	  // String[] queries = new String[] {"", "?action=go", "?Search=new"};
	   
	   UrlValidator urlVal7 = new UrlValidator();

	   System.out.println();
	   System.out.println();
	   System.out.println(">> Start testing valid authority ONLY...");
	   System.out.println();
	   System.out.println();
	   for (int i = 0; i < NUM_TESTS_7; i++) {
	       // String Scheme6 = randomSelect(validSchemes);
	       String Authority7 = randomSelect(validAuthorities);
	       // String Ports1 = randomSelect(validPorts);
	       // String Paths4 = randomSelect(validPaths);
	       // String Query3 = randomSelect(queries); 
	       
	       // build a full URL to test from random selections
	       String URL = Authority7;
	       System.out.println(URL + "  is under test.");
	       assertTrue(URL, urlVal7.isValid(URL)); 
	   }  
	   System.out.println();
	   System.out.println();
	   System.out.println(">> Finished testing valid authority ONLY...NO ERRORS DETECTED!!!"); 
	   System.out.println();
	   System.out.println();
   }
   
   
   // manual partition for stand alone testing
   public void testYourEigthPartition() {
	   UrlValidator urlVal8 = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String URL = "http://256.256.256.256";
	   assertFalse(URL, urlVal8.isValid(URL));
	   
   }
   
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   //You can use this function for programming based testing
	   
	   // loop through various URL structures
	   
	   // unit test: test a specific part of the url structure
	   
	   // first unit test: http://(domain name)
	   // bug in ResultPair: boolean value passed as second argument is negated;
	   // i.e. ResultPair.valid = !(second argument)
	   // so ResultPair("www.google.com", true) should be true but is false instead
	   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", !true),
                                  new ResultPair("go.com", !true),
                                  new ResultPair("go.au", !true),
                                  new ResultPair("0.0.0.0", !true),
                                  new ResultPair("255.255.255.255", !true),
                                  new ResultPair("256.256.256.256", !false),
                                  new ResultPair("255.com", !true),
                                  new ResultPair("1.2.3.4.5", !false),
                                  new ResultPair("1.2.3.4.", !false),
                                  new ResultPair("1.2.3", !false),
                                  new ResultPair(".1.2.3.4", !false),
                                  new ResultPair("go.a", !false),
								  new ResultPair("go.a1a", !false),
                                  new ResultPair("go.1aa", !false),
                                  new ResultPair("aaa.", !false),
                                  new ResultPair(".aaa", !false),
                                  new ResultPair("aaa", !false),
                                  new ResultPair("", !false)
		};
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //this constructor was used to verify a teammate's bug
	   //UrlValidator urlVal = new UrlValidator();
		for (int i = 0; i < testUrlAuthority.length; i++){
			boolean expected = true;
			String url = "http://";
            url = url + testUrlAuthority[i].item;
            expected &= testUrlAuthority[i].valid;
			boolean result = urlVal.isValid(url);
			if (result){
				System.out.println(url + " Expected: " + expected + " Actual: " + result);
			}
			assertEquals(url, expected, result);
		}

   }
   
	public static void main(String[] argv) {
		  UrlValidatorTest tester = new UrlValidatorTest("url test");
		  tester.testManualTest();
		  tester.testYourFirstPartition();
		  tester.testYourSecondPartition();
		  tester.testYourThirdPartition();
		  tester.testYourFourthPartition();
		  tester.testYourFifthPartition();
		  tester.testYourSixthPartition();
		  tester.testYourSeventhPartition();
		  tester.testYourEigthPartition();
		  tester.testIsValid();
	   }

}
