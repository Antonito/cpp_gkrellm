#ifndef AWINDOW_HPP_
#define AWINDOW_HPP_

#include <map>
#include <cstdlib>
#include <iterator>
#include "AFrame.hpp"

namespace Graphic
{
  class AWindow
  {
  public:
    AWindow(std::string const &name);
    virtual ~AWindow();

    void addTab(std::string const &name, AFrame &tab);
    void         nextTab();
    void         prevTab();
    virtual void updateInfos() = 0;
    void         enable();
    void         disable();
    virtual bool update() = 0;
    virtual void refresh() const = 0;

  protected:
    std::string m_name;
    std::map<std::string, AFrame *>           m_tab;
    std::map<std::string, AFrame *>::iterator m_currentTab;
    size_t m_headerSize;
    size_t m_width;
    size_t m_height;
  };
}

#endif // !AWINDOW_HPP_