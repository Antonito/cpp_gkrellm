#ifndef AFRAME_HPP_
#define AFRAME_HPP_

#include <vector>
#include <cstdlib>
#include "IMonitorDisplay.hpp"

namespace Graphic
{
  class AFrame
  {
  public:
    enum SplitMode
    {
      VERTICAL,
      HORIZONTAL
    };
    virtual ~AFrame(){};

    virtual void enable(size_t x, size_t y, size_t offX, size_t offY,
                        size_t width, size_t height) = 0;
    virtual void disable() = 0;
    void addFrame(AFrame *frame);
    void removeFrame(size_t index);
    bool                   isEnabled() const;
    IMonitorDisplay const *getModule() const;
    void setModule(IMonitorDisplay *module);
    virtual void update() = 0;
    virtual void refresh() = 0;
    double       getRatio() const;
    void setRatio(double r);
    SplitMode getSplitMode() const;
    void setSplitMode(SplitMode s);

    static AFrame *newFrame();

  protected:
    AFrame();
    std::vector<AFrame *> m_split;
    double                m_ratio;
    IMonitorDisplay *     m_module;
    SplitMode             m_splitMode;
    size_t                m_x;
    size_t                m_y;
    size_t                m_offX;
    size_t                m_offY;
    size_t                m_width;
    size_t                m_height;
    bool                  m_isEnabled;
  };
}

#endif // !AFRAME_HPP_