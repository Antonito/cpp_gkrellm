#include <string>
#include <fstream>
#include "Misc.hpp"
#include "UtilsModule.hpp"
#include "Logger.hpp"
#include "HTTPServer.hpp"
#include "Misc.hpp"

namespace Module
{

  Misc::MiscGlobal *Misc::m_data = NULL;

  Misc::Misc()
  {
  }

  Misc::~Misc()
  {
  }

  void Misc::setData(MiscGlobal *ng)
  {
    m_data = ng;
  }

  std::string Misc::miscSerializer()
  {
    std::stringstream nb;
    std::string       json = "{";
    json += "\"brightness\": ";
    nb.str("");
    nb << m_data->brightness;
    json += nb.str();
    json += ", \"brightness_max\": ";
    nb.str("");
    nb << m_data->brightnessMax;
    json += nb.str();
    json += ", \"capslock\": ";
    nb.str("");
    nb << m_data->capslock;
    json += nb.str();
    json += ", \"numlock\": ";
    nb.str("");
    nb << m_data->capslock;
    json += nb.str();
    json += ", \"mac_addr\": \"";
    json += m_data->macaddr;
    json += "\"}";
    return (json);
  }

  void Misc::setRoute()
  {
    Logger::Instance().log(Logger::Info, "Added routes for Misc Module.");
    HTTPServer::addRoute("/misc", static_cast<HTTPServer::serializerToJSON>(
                                      &Misc::miscSerializer));
  }

  void Misc::parse()
  {
    std::ifstream     ff;
    std::stringstream mystream;

    ff.open("/sys/class/backlight/intel_backlight/actual_brightness",
            std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream << ff.rdbuf();
    mystream >> m_data->brightness;
    ff.close();
    ff.open("/sys/class/backlight/intel_backlight/max_brightness",
            std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream << ff.rdbuf();
    mystream >> m_data->brightnessMax;
    ff.close();
    ff.open("/sys/class/leds/input0::capslock/brightness", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream << ff.rdbuf();
    mystream >> m_data->capslock;
    ff.close();
    ff.open("/sys/class/leds/input0::numlock/brightness", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream << ff.rdbuf();
    mystream >> m_data->numlock;
    ff.close();
    ff.open("/sys/class/ieee80211/phy0/macaddress", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream << ff.rdbuf();
    mystream >> m_data->macaddr;
    ff.close();
  }
}