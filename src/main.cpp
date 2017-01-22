#include <iostream>
#include <unistd.h>
#include "MainManager.hpp"
#include "AModule.hpp"
#include "ncurses/NcNetwork.hpp"
#include "Frame.hpp"
#include "SfWindow.hpp"
#include "SfFrame.hpp"

Graphic::Event ncurseMode(MainManager const &)
{
  Graphic::Event           retValue;
  Graphic::Ncurses::Window win("gkrellm");
  Graphic::Ncurses::Frame *frm = new Graphic::Ncurses::Frame();

  win.addTab("TabName", *frm);
  // Network

  //

  win.enable();
  while ((retValue = win.update()) == Graphic::CONTINUE)
    win.refresh();
  return (retValue);
}

Graphic::Event sfmlMode(MainManager const &)
{
  Graphic::Event retValue = Graphic::CONTINUE;

  Graphic::SFML::SfWindow win("Window", 1280, 720);
  Graphic::SFML::SfFrame *frm = new Graphic::SFML::SfFrame(win);

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
