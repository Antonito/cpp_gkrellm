#include <iostream>
#include <ncurses.h>
#include "Window.hpp"

int main()
{
  union
  {
    uint8_t  byte[2];
    uint16_t value;
  };
  value = KEY_F(3);
  std::cout << KEY_F(3) << std::endl;
  std::cout << (int)byte[0] << ", " << (int)byte[1] << std::endl;
  Graphic::Ncurses::Window win("Window");
  Graphic::AFrame *        frame = Graphic::AFrame::newFrame();
  Graphic::AFrame *        child1 = Graphic::AFrame::newFrame();
  Graphic::AFrame *        child2 = Graphic::AFrame::newFrame();
  Graphic::AFrame *        schild1 = Graphic::AFrame::newFrame();
  Graphic::AFrame *        schild2 = Graphic::AFrame::newFrame();

  frame->addFrame(child1);
  frame->addFrame(child2);
  child1->addFrame(schild1);
  child1->addFrame(schild2);
  child1->setRatio(0.4);
  child1->setSplitMode(Graphic::AFrame::HORIZONTAL);
  win.addTab("Tab1", *frame);
  frame->setRatio(0.7);
  win.enable();
  while (win.update())
    win.refresh();
  return (0);
}