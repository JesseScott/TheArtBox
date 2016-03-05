

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