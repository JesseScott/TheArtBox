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

void setup()
{
  fullScreen(SPAN);
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




void draw()
{
  background(0);
  
  drawImageScreen(pgwidth * 0);
  drawMetaScreen (pgwidth * 1);
  drawNewsScreen (pgwidth * 2);
}