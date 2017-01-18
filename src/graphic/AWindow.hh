#ifndef AWINDOW_HH_
#define AWINDOW_HH_

class AWindow
{
public:
  AWindow();
  virtual ~AWindow() = 0;

  virtual resize(size_t width, size_t height) = 0;
  virtual close() = 0;
  virtual update() = 0;

private:
  size_t m_width;
  size_t m_height;
};

#endif // !AWINDOW_HH_