// 0192837465

JSONObject json;
String BASEPATH = "../MEDIA/json/";
String FILENAME = "article.json";
ArrayList<Article> mArticles = new ArrayList<Article>();


void setup()
{
  size(500, 500);
  
    // JSON
    if(readJSON())
    {
        writeJSONToArticleArray();
    }
  
}




void draw()
{
  
  
  
}