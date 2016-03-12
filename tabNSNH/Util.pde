
private float startingHorizontalPositionForString(String _str)
{
  float x = 0.f;
  float w = textWidth(_str);
  x = ( (pgwidth-w)-(w/4) );
  return x;
}