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
    
    Article(){}
    
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
        println("\nARTCILE: \nTITLE:\t" + title + "\n" + "SUB:\t\t" + subtitle + "\n" + "BODY:\t" + body + "\n" + "DATE:\t" + date);
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
        fill(50);
        textFont(mTitleFont);
        text("TITLE", mXPos + mWidth/2 /*- (mTitleFont.stringWidth(title)/2)*/, 96);
        line(mXPos + 54, 104, width - 54, 104);
        
        textFont(mSubtitleFont);
        text("subtitle subtitle", mXPos + mWidth/2 /*- (mTitleFont.stringWidth(title))*/, 144);
    
        String b = "asdsadsads asdsadsadj  asdsa dsadsa  asd sdjl kask asdlsajd   \nlasjdsalj dasld  lsjdslajddas lsa ";
        textFont(mBodyFont);
        text(b, mXPos + 54, 192);  
    }
    
    
}