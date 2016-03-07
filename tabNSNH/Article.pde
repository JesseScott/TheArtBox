class Article {
   
 
    int    yOffset;
    PFont  mTitleFont;
    PFont  mSubtitleFont;
    PFont  mBodyFont;
    int mWidth = pgwidth;
    int mXPos = pgwidth * 2;
    
    private String title;
    private String subtitle;
    private String body;
    private String date;
    
    
    // Constructors
    
    Article()
    {
      setup();
    }
    
    Article(String _title, String _subtitle, String _body, String _date)
    {
        title = _title;
        subtitle = _subtitle;
        body = _body;
        date = _date;
        
        setup();
    }
    
    
    // Getters
  
    public String getTitle()
    {
        return title;
    }
    
    public String getSubtitle()
    {
        return subtitle;
    }
    
    public String getBody()
    {
        return body;
    }
    
    public String getDate()
    {
        return date;
    }
  
    // Log
  
    public void logData()
    {
        println("\nARTCILE: \nTITLE:\t" + title + "\n" + "SUB:" + subtitle + "\n" + "BODY:\t" + body + "\n" + "DATE:\t" + date);
    }
  
    // Present
  
    public void setup()
    {
        mTitleFont     = createFont("fonts/Open Sans.ttf", 32);
        mSubtitleFont  = createFont("fonts/Open Sans.ttf", 24);
        mBodyFont      = createFont("fonts/Open Sans.ttf", 14);
    }
  
    public void update()
    {
        
    }
  
    public void draw()
    {
        fill(255);
        textFont(mTitleFont);
        text("TITLE", mXPos + mWidth/2 /*- (mTitleFont.stringWidth(title)/2)*/, 96);
        line(mXPos + 54, 104, width - 54, 104);
        
        textFont(mSubtitleFont);
        text("subtitle subtitle", mXPos + mWidth/2 /*- (mTitleFont.stringWidth(title))*/, 144);
    
        String b = "asdsadsads asdsadsadj  asdsa dsadsa  asd sdjl kask asdlsajd   \nlasjdsalj dasld  lsjdslajddas lsa ";
        textFont(mBodyFont);
        text(b, mXPos + 54, 192);  
    }
    
        public void drawDebug()
    {
        fill(255); stroke(255);
        textFont(mTitleFont);
        text("THIS WILL BE A TITLE", mXPos + mWidth/4 /*- (mTitleFont.stringWidth(title)/2)*/, pgheight/4);
        line(mXPos + 54, pgheight/4 + 8, width - 54, pgheight/4 + 8);
        
        textFont(mSubtitleFont);
        text("and this will be a subtitle", mXPos + mWidth/4 + 20 /*- (mTitleFont.stringWidth(title))*/, pgheight/4 + 48);
    
        String b = "This is a body.\n\nThere will be various types of information here, depeniding upon what type\nof post this is.\n\nBlogs, Events, Articles, and Community Announcements are \npossible types";
        textFont(mBodyFont);
        text(b, mXPos + 54, pgheight/4 + 96);  
    }
    
    
}