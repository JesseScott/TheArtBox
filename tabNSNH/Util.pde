
private float startingHorizontalPositionForString(String _str)
{
  float x = 0.f;
  
  x = ( (pgwidth-textWidth(_str))-(textWidth(_str)/4) );
  
  return x;
}