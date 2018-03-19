 public void testManualTest()
   {
     
	 //UrlValidator urlValidator2 = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
     String[] schemes = {"http","https", "files", "ftp"};
     //UrlValidator urlValidator2 = new UrlValidator(schemes);
     UrlValidator urlValidator2 = new UrlValidator(schemes, UrlValidator.NO_FRAGMENTS);
     
     String[] validUrls = {"http://www.toga.com:21", "https://www.amazon.com/80", "ftp://dropbox.com", "https://www.google.com/"};
     String[] invalidUrls = {"https://www.amazon.com:80000", "ftp:://foo.bar.com/", "dog...dog", "tim.jones.com"};
     
     for (int i = 0; i < invalidUrls.length; i++) {
	       
    	 //System.out.println((urlValidator2.isValid(invalidUrls[i])));
		 assertFalse(urlValidator2.isValid(invalidUrls[i]));
	 }
	 	
     
     for (int i = 0; i < validUrls.length; i++) {
       
    	 	assertTrue(urlValidator2.isValid(validUrls[i]));
    	    //System.out.println((urlValidator2.isValid(validUrls[i])));
     }