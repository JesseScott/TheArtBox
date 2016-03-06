// 0192837465

JSONObject json;
String BASEPATH = "../MEDIA/json/";
String FILENAME = "article.json";
ArrayList<Article> mArticles = new ArrayList<Article>();
int current_article = 0;
PGraphics image_buffer;
PGraphics meta_buffer;
PGraphics news_buffer;

private static final int pgwidth = 540;
private static final int pgheight = 960;

void setup()
{
  size(1620, 960);
  
    // JSON
    if(readJSON())
    {
        writeJSONToArticleArray();
    }
    
    // PGraphics
    image_buffer = createGraphics(pgwidth, pgheight);
    meta_buffer  = createGraphics(pgwidth, pgheight);
    news_buffer  = createGraphics(pgwidth, pgheight);
  
}




void draw()
{
  background(0);
  
  drawImageScreen(pgwidth * 0);
  drawMetaScreen (pgwidth * 1);
  drawNewsScreen (pgwidth * 2);
}