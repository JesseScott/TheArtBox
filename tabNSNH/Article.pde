class Article {
   
    // Vars
    
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
        mTitleFont     = createFont("fonts/Open Sans.ttf", pgwidth * 0.075);
        mSubtitleFont  = createFont("fonts/Open Sans.ttf", pgwidth * 0.050);
        mBodyFont      = createFont("fonts/Open Sans.ttf", pgwidth * 0.025);
    }
  
    public void update()
    {
        
    }
  
    public void draw()
    {
        fill(255);
        textFont(mTitleFont);
        String title = "TITLE";
        text(title, mXPos + (pgwidth/2)-(textWidth(title)/2), 96);
        line(mXPos + 54, 104, mXPos + mWidth - 54, 104);
        
        textFont(mSubtitleFont);
        String subtitle = "subtitle subtitle";
        text(subtitle, mXPos + (pgwidth/2)-(textWidth(subtitle)/2), 144);
    
        textFont(mBodyFont);
        String body = "asdsadsads asdsadsadj  asdsa dsadsa  asd sdjl kask asdlsajd   \nlasjdsalj dasld  lsjdslajddas lsa ";
        text(body, mXPos + (pgwidth/2)-(textWidth(body)/2), 192);
    }
    
    public void drawDebug()
    {
        fill(255); 
        stroke(255);
        textFont(mTitleFont);
        text("THIS WILL BE A TITLE", mXPos + mWidth/6 , pgheight/4);
        line(mXPos + (pgwidth/10), pgheight/4 + 16, width - (pgwidth/10), pgheight/4 + 16);
        
        textFont(mSubtitleFont);
        text("and this will be a subtitle", mXPos + mWidth/4 + 20, pgheight/4 + 72);
    
        String b = "This is a text body.\n\nThere will be various types of information here, depeniding upon what type\nof post this is.\n\nBlogs, Events, Articles, and Community Announcements are \npossible types";
        textFont(mBodyFont);
        text(b, mXPos + (pgwidth/10), pgheight/2);  
    }
    
    
}