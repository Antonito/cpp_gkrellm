#include <iostream>
#include <unistd.h>
#include "MainManager.hpp"
#include "AModule.hpp"
#include "ncurses/NcNetwork.hpp"
#include "Frame.hpp"
#include "SfWindow.hpp"
#include "SfFrame.hpp"
#include "SfNetwork.hpp"
#include "ncurses/NcCpu.hpp"

// NCURSES

Graphic::Event ncurseMode(MainManager &m)
{
  Graphic::Event           retValue;
  Graphic::Ncurses::Window win("gkrellm");
  Graphic::Ncurses::Frame *frame1 = new Graphic::Ncurses::Frame();

  Graphic::Ncurses::Frame *frame1_1 = new Graphic::Ncurses::Frame();
  Graphic::Ncurses::Frame *frame1_2 = new Graphic::Ncurses::Frame();

  Graphic::Module::Ncurses::NcNetwork *network =
      new Graphic::Module::Ncurses::NcNetwork(frame1_1, m.getModuleManager());
  Graphic::Module::Ncurses::NcCpu *cpu =
        new Graphic::Module::Ncurses::NcCpu(frame1_2, m.getModuleManager());

  frame1_1->setModule(network);
  frame1_2->setModule(cpu);

  win.addTab("TabName", *frame1);
  // Network

  frame1->setSplitMode(Graphic::AFrame::HORIZONTAL);
  frame1->addFrame(frame1_1);
  frame1->addFrame(frame1_2);

  //
  frame1->setModule(network);

  win.enable();
  while ((retValue = win.update()) == Graphic::CONTINUE)
    win.refresh();
  return (retValue);
}

// SFML

Graphic::Event sfmlMode(MainManager &manager)
{
  Graphic::Event retValue = Graphic::CONTINUE;

  Graphic::SFML::SfWindow win("Window", 1280, 720);
  Graphic::SFML::SfFrame *frm = new Graphic::SFML::SfFrame(win);
  //(void)manager;
  SfNetwork *network = new SfNetwork(frm, manager.getModuleManager());
  frm->setModule(network);

  win.addTab("TabName", *frm);
  win.enable();
  while (win.isOpen() && retValue == Graphic::CONTINUE)
    {
      retValue = win.update();
      win.refresh();
    }
  return (retValue);
}

int main()
{
  MainManager    manager;
  Graphic::Event retVal = Graphic::CONTINUE;
  Graphic::Mode  graphicMode = Graphic::NCURSES_MODE;
  //   for (;;)
  //     usleep(10000);
  while (retVal == Graphic::CONTINUE)
    {
      if (graphicMode == Graphic::NCURSES_MODE)
	retVal = ncurseMode(manager);
      else
	retVal = sfmlMode(manager);

      if (retVal == Graphic::SWITCH_MODE)
	{
	  graphicMode = (graphicMode == Graphic::SFML_MODE)
	                    ? Graphic::NCURSES_MODE
	                    : Graphic::SFML_MODE;
	  retVal = Graphic::CONTINUE;
	}
      else
	break;
    }

  if (retVal == Graphic::ERROR)
    return (1);
  return (0);
}
