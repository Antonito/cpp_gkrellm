#include <string>
#include <fstream>
#include "Power.hpp"
#include "UtilsModule.hpp"
#include "Logger.hpp"
#include "HTTPServer.hpp"
#include "Power.hpp"

namespace Module
{

  Power::PowerGlobal *Power::m_data = NULL;

  Power::Power()
  {
  }

  Power::~Power()
  {
  }

  void Power::setData(PowerGlobal *ng)
  {
    m_data = ng;
  }

  std::string Power::powerSerializer()
  {
    std::stringstream nb;
    std::string       json = "{ \"battery\": {";
    json += "\"manufacturer\": \"";
    json += m_data->batManufacturer;
    json += "\", \"technology\": \"";
    json += m_data->batTechnology;
    json += "\", \"status\": \"";
    json += m_data->batStatus;
    json += "\", \"model_name\": \"";
    json += m_data->batModelName;
    json += "\", \"capacity\": ";
    nb.str("");
    nb << m_data->batCapacity;
    json += nb.str();
    json += ", \"charge_full\": ";
    nb.str("");
    nb << m_data->batChargeFull;
    json += nb.str();
    json += ", \"charge_now\": ";
    nb.str("");
    nb << m_data->batChargeNow;
    json += nb.str();
    json += ", \"current_now\": ";
    nb.str("");
    nb << m_data->batCurrentNow;
    json += nb.str();
    json += ", \"voltage_now\": ";
    nb.str("");
    nb << m_data->batVoltageNow;
    json += nb.str();
    json += ", \"alarm\": ";
    nb.str("");
    nb << m_data->batAlarm;
    json += nb.str();
    json += "}, \"AC\": { ";
    json += "\"online\": ";
    nb.str("");
    nb << m_data->ACOnline;
    json += nb.str();
    json += ", \"type\": \"";
    json += m_data->ACType;
    json += "\"";
    json += "}}";
    return (json);
  }

  void Power::setRoute()
  {
    Logger::Instance().log(Logger::Info, "Added routes for Power Module.");
    HTTPServer::addRoute("/power", static_cast<HTTPServer::serializerToJSON>(
                                       &Power::powerSerializer));
  }

  void Power::parse()
  {
    std::ifstream     ff;
    std::stringstream mystream;

    ff.open("/sys/class/power_supply/BAT0/capacity", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream << ff.rdbuf();
    mystream >> m_data->batCapacity;
    ff.close();
    ff.open("/sys/class/power_supply/BAT0/charge_full", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->batChargeFull;
    ff.close();
    ff.open("/sys/class/power_supply/BAT0/manufacturer", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->batManufacturer;
    ff.close();
    ff.open("/sys/class/power_supply/BAT0/technology", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->batTechnology;
    ff.close();
    ff.open("/sys/class/power_supply/BAT0/status", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->batStatus;
    ff.close();
    ff.open("/sys/class/power_supply/BAT0/model_name", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->batModelName;
    ff.close();
    ff.open("/sys/class/power_supply/BAT0/current_now", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->batCurrentNow;
    ff.close();
    ff.open("/sys/class/power_supply/BAT0/alarm", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->batAlarm;
    ff.close();
    ff.open("/sys/class/power_supply/BAT0/charge_now", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->batChargeNow;
    ff.close();
    ff.open("/sys/class/power_supply/BAT0/voltage_now", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->batVoltageNow;
    ff.close();
    ff.open("/sys/class/power_supply/AC/online", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->ACOnline;
    ff.close();
    ff.open("/sys/class/power_supply/AC/type", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "cannot read power module info");
	return;
      }
    mystream.str("");
    mystream << ff.rdbuf();
    mystream >> m_data->ACType;
    ff.close();
  }
}