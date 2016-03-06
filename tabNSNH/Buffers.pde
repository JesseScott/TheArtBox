
private void drawImageScreen(int xpos)
{
  image_buffer.beginDraw();
    //fill(255, 0, 0);
    //rect(xpos, 0, pgwidth, pgheight);
    
    stroke(255);
    line(xpos + 54, 192, pgwidth - 54, 192); // top
    line(xpos + 54, 192, xpos + 54, 624); // left
    line(pgwidth - 54, 624, pgwidth - 54, 192); // right
    line(xpos + 54, 624, pgwidth - 54, 624); // bottom
    line(xpos + 54, 192, pgwidth - 54, 624); // cross dr
    line(xpos + 54, 624, pgwidth - 54, 192); // cross dl
    
    fill(255);
    textSize(24);
    text("--this will be an image --", xpos + pgwidth/4, 700);   
    
  image_buffer.endDraw();
  image(image_buffer, xpos, 0, pgwidth, pgheight); 
}

private void drawMetaScreen(int xpos)
{
  meta_buffer.beginDraw();
    fill(255);
    //rect(xpos, 0, pgwidth, pgheight);
    textSize(60);
    text("--COMING SOON --", xpos + pgwidth/16, pgheight/4);
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