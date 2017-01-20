#ifndef AGRAPHICFRAME_HH_
#define AGRAPHICFRAME_HH_

#include <cstddef>

namespace Graphic
{
  class AGraphicFrame
  {
  public:
    AGraphicFrame(size_t posX, size_t posY, size_t width, size_t height);
    AGraphicFrame(AGraphicFrame const &o);
    virtual ~AGraphicFrame() = 0;

    AGraphicFrame &operator=(AGraphicFrame const &other);

  protected:
    size_t m_x;
    size_t m_y;
    size_t m_width;
    size_t m_height;
  };
}

#endif // !AGRAPHICFRAME_HH_