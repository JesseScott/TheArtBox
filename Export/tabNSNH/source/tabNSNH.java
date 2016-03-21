import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class tabNSNH extends PApplet {

// 0192837465

JSONObject json;
String BASEPATH = "../MEDIA/json/";
String FILENAME = "article.json";
ArrayList<Article> mArticles = new ArrayList<Article>();
int current_article = 0;
PGraphics image_buffer;
PGraphics meta_buffer;
PGraphics news_buffer;

private static final int pgwidth = 1080;
private static final int pgheight = 1920;

public void setup()
{
  
  //size(3240, 1920);
  
    // JSON
    //if(readJSON())
    //{
    //    writeJSONToArticleArray();
    //}
    Article tmp = new Article();
    mArticles.add(tmp);
    
    // PGraphics
    image_buffer = createGraphics(pgwidth, pgheight);
    meta_buffer  = createGraphics(pgwidth, pgheight);
    news_buffer  = createGraphics(pgwidth, pgheight);
  
}




public void draw()
{
  background(0);
  
  drawImageScreen(pgwidth * 0);
  drawMetaScreen (pgwidth * 1);
  drawNewsScreen (pgwidth * 2);
}
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
        mTitleFont     = createFont("fonts/Open Sans.ttf", 72);
        mSubtitleFont  = createFont("fonts/Open Sans.ttf", 48);
        mBodyFont      = createFont("fonts/Open Sans.ttf", 24);
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
        text("THIS WILL BE A TITLE", mXPos + mWidth/6 , pgheight/4);
        line(mXPos + (pgwidth/10), pgheight/4 + 16, width - (pgwidth/10), pgheight/4 + 16);
        
        textFont(mSubtitleFont);
        text("and this will be a subtitle", mXPos + mWidth/4 + 20, pgheight/4 + 72);
    
        String b = "This is a text body.\n\nThere will be various types of information here, depeniding upon what type\nof post this is.\n\nBlogs, Events, Articles, and Community Announcements are \npossible types";
        textFont(mBodyFont);
        text(b, mXPos + (pgwidth/10), pgheight/2);  
    }
    
    
}

private void drawImageScreen(int xpos)
{
  image_buffer.beginDraw();
  //fill(255, 0, 0);
  //rect(xpos, 0, pgwidth, pgheight);
  int pad = pgwidth/10;
  int top = pgheight/8;
  stroke(255);
  line(xpos + pad, top + pad * 2, pgwidth - pad, top + pad * 2); // top
  line(xpos + pad, top + pad * 2, xpos + pad, pad * 10); // left
  line(pgwidth - pad, pad * 10, pgwidth - pad, top + pad * 2); // right
  line(xpos + pad, pad * 10, pgwidth - pad, pad * 10); // bottom
  line(xpos + pad, top + pad * 2, pgwidth - pad, pad * 10); // cross dr
  line(xpos + pad, pad * 10, pgwidth - pad, top + pad * 2); // cross dl
  
  fill(255);
  textSize(48);
  text("--this will be an image --", xpos + pgwidth/4, pgheight/2 + pad * 2);   
    
  image_buffer.endDraw();
  image(image_buffer, xpos, 0, pgwidth, pgheight); 
}

private void drawMetaScreen(int xpos)
{
  meta_buffer.beginDraw();
    fill(255);
    //rect(xpos, 0, pgwidth, pgheight);
    textSize(96);
    text("--COMING SOON --", xpos + pgwidth/8, pgheight/2);
  meta_buffer.endDraw();
  image(meta_buffer, xpos, 0, pgwidth, pgheight); 
}

private void drawNewsScreen(int xpos)
{
  news_buffer.beginDraw();
    //fill(0, 0, 255);
    //rect(xpos, 0, pgwidth, pgheight);
    mArticles.get(current_article).drawDebug();
  news_buffer.endDraw();
  image(news_buffer, xpos, 0, pgwidth, pgheight); 
}


private boolean readJSON()
{
    String path = BASEPATH + FILENAME;
    json = loadJSONObject(path);    
    if (json != null)
    {
        println("Parsed JSON! :D ");
        return true;
    }
    else
    {
        println("Failed to Parse JSON :( ");
        return false;
    }
}

private void writeJSONToArticleArray()
{
  //print(json);
  JSONArray results = json.getJSONArray("results");
  //print(results);
  
  for(int i = 0; i < results.size(); i++)
  {
       // Read Vars From JSON
       JSONObject obj = results.getJSONObject(i); 
       String title = obj.getString("title");
       String subtitle = obj.getString("subtitle");
       String body = obj.getString("body");
       String date = obj.getString("createdAt");
       
       //print(title + "\t" + subtitle + "\t" + body + "\t" + date);
       
       // Add To Articles
       Article art = new Article(title, subtitle, body, date);
       mArticles.add(art);
  }
  
  for (int i = 0; i < mArticles.size(); i++) {
       mArticles.get(i).logData();
  }
  
}
  public void settings() {  fullScreen(SPAN); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "tabNSNH" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
