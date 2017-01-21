#include <unistd.h>
#include "MainManager.hpp"
#include "AModule.hpp"
#include "ncurses/NcNetwork.hpp"
#include "Frame.hpp"

int main()
{
  MainManager manager;

  Graphic::Ncurses::Window win("Window");
  Graphic::Ncurses::Frame *frame = new Graphic::Ncurses::Frame();
  Graphic::Ncurses::Frame *child1 = new Graphic::Ncurses::Frame();
  Graphic::Ncurses::Frame *child2 = new Graphic::Ncurses::Frame();
  Graphic::Ncurses::Frame *schild1 = new Graphic::Ncurses::Frame();
  Graphic::Ncurses::Frame *schild2 = new Graphic::Ncurses::Frame();

  Graphic::AModule *network = new Graphic::Module::Ncurses::NcNetwork(schild1);

  frame->addFrame(child1);
  frame->addFrame(child2);
  child1->addFrame(schild1);
  child1->addFrame(schild2);
  child1->setRatio(0.4);
  child1->setSplitMode(Graphic::AFrame::HORIZONTAL);
  schild1->setModule(network);
  win.addTab("Tab1", *frame);
  frame->setRatio(0.7);
  win.enable();
  while (win.update())
    win.refresh();
  return (0);
}
