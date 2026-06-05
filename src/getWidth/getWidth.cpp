int getWidth(int number) {
  int width = 1;
  while (number >= 10) {
    float quotient = number / 10;
    number = static_cast<int>(quotient);
    width += 1;
  }
  return width;
}
