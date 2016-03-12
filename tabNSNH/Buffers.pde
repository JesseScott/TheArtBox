
private void drawImageScreen(int xpos)
{
  image_buffer.beginDraw();
  
  if(DEBUG) 
  {
    fill(255, 0, 0, 50);
    rect(xpos, 0, pgwidth, pgheight);
    
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
    textSize(pgwidth * 0.05);
    String msg = "--this will be an image --";
    text(msg, xpos + ((pgwidth-textWidth(msg))-(textWidth(msg)/4)), pgheight/2 + pad * 2);   
  }
  
  image_buffer.endDraw();
  image(image_buffer, xpos, 0, pgwidth, pgheight); 
}

private void drawMetaScreen(int xpos)
{
  meta_buffer.beginDraw();
  
  if(DEBUG) 
  {
    fill(0, 255, 0, 50);
    rect(xpos, 0, pgwidth, pgheight);
    textSize(pgwidth * 0.1);
    String msg = "--COMING SOON --";
    text(msg, xpos + (pgwidth-textWidth(msg)), pgheight/2);
  }
  
  meta_buffer.endDraw();
  image(meta_buffer, xpos, 0, pgwidth, pgheight); 
}

private void drawNewsScreen(int xpos)
{
  news_buffer.beginDraw();
  
  if(DEBUG) 
  {  
    fill(0, 0, 255, 50);
    stroke(255, 50);
    rect(xpos, 0, pgwidth, pgheight);
    mArticles.get(current_article).draw();
  }
  
  news_buffer.endDraw();
  image(news_buffer, xpos, 0, pgwidth, pgheight); 
}