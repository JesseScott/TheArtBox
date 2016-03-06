
private void drawImageScreen(int xpos)
{
  image_buffer.beginDraw();
    fill(255, 0, 0);
    rect(xpos, 0, pgwidth, pgheight);
  image_buffer.endDraw();
  image(image_buffer, xpos, 0, pgwidth, pgheight); 
}

private void drawMetaScreen(int xpos)
{
  meta_buffer.beginDraw();
    fill(0, 255, 0);
    rect(xpos, 0, pgwidth, pgheight);
  meta_buffer.endDraw();
  image(meta_buffer, xpos, 0, pgwidth, pgheight); 
}

private void drawNewsScreen(int xpos)
{
  news_buffer.beginDraw();
    fill(0, 0, 255);
    rect(xpos, 0, pgwidth, pgheight);
    mArticles.get(current_article).draw();
  news_buffer.endDraw();
  image(news_buffer, xpos, 0, pgwidth, pgheight); 
}