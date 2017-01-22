#include <iostream>
#include <cstring>
#include <unistd.h>
#include "MainManager.hpp"
#include "AModule.hpp"
#include "ncurses/NcNetwork.hpp"
#include "Frame.hpp"
#include "SfWindow.hpp"
#include "SfFrame.hpp"
#include "SfNetwork.hpp"
#include "ncurses/NcCpu.hpp"
#include "NcSystem.hpp"
#include "Logger.hpp"

// NCURSES

Graphic::Event ncurseMode(MainManager &m)
{
  Graphic::Event           retValue;
  Graphic::Ncurses::Window win("gkrellm");
  Graphic::Ncurses::Frame *frame1 = new Graphic::Ncurses::Frame();
  frame1->setSplitMode(Graphic::AFrame::HORIZONTAL);

  // Network
  Graphic::Ncurses::Frame *frame1_1 = new Graphic::Ncurses::Frame();
  Graphic::Module::Ncurses::NcNetwork *network =
      new Graphic::Module::Ncurses::NcNetwork(frame1_1, m.getModuleManager());
  frame1_1->setModule(network);
  frame1->addFrame(frame1_1);

  // SPLIT

  // System
  Graphic::Ncurses::Frame *frame1_2 = new Graphic::Ncurses::Frame();
  Graphic::Ncurses::Frame *frame1_2_1 = new Graphic::Ncurses::Frame();
  Graphic::Module::Ncurses::NcSystem *system =
      new Graphic::Module::Ncurses::NcSystem(frame1_2_1, m.getModuleManager());
  frame1_2_1->setModule(system);
  frame1_2->addFrame(frame1_2_1);

  // Cpu
  Graphic::Ncurses::Frame *        frame1_2_2 = new Graphic::Ncurses::Frame();
  Graphic::Module::Ncurses::NcCpu *cpu =
      new Graphic::Module::Ncurses::NcCpu(frame1_2_2, m.getModuleManager());
  frame1_2_2->setModule(cpu);
  frame1_2->addFrame(frame1_2_2);
  frame1->addFrame(frame1_2);

  win.addTab("TabName", *frame1);
  // Network

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

  Graphic::SFML::SfWindow win("gkrellm", 1280, 720);
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

static int graphic_mode(MainManager &manager)
{
  Graphic::Event retVal = Graphic::CONTINUE;
  Graphic::Mode  graphicMode = Graphic::NCURSES_MODE;
  Logger &       logger = Logger::Instance();

    while (retVal == Graphic::CONTINUE)
    {
      if (graphicMode == Graphic::NCURSES_MODE)
	{
	  logger.log(Logger::Info, "Entering text mode [NCURSES]");
	  retVal = ncurseMode(manager);
	  logger.log(Logger::Info, "Leaving text mode [NCURSES]");
	}
      else
	{
	  logger.log(Logger::Info, "Entering graphic text mode [SFML]");
	  retVal = sfmlMode(manager);
	  logger.log(Logger::Info, "Leaving graphic text mode [SFML]");
	}

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
    return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
  MainManager    manager;

  if (ac == 2 && !::strcmp(av[1], "--server"))
    {
      Logger::Instance().log(Logger::Info, "Starting in server mode");
      for (;;)
	{
	  sleep(1);
	}
    }
  return (graphic_mode(manager));
}
