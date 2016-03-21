
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