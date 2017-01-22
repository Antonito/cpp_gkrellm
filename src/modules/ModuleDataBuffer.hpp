#ifndef MODULEDATABUFFER_HPP_
#define MODULEDATABUFFER_HPP_

// This module describes the ModuleDataBuffer which contains every information
// collected by the data miner threads

#include "CPU.hpp"
#include "Network.hpp"
#include "System.hpp"
#include "Disk.hpp"
#include "RAM.hpp"
#include "Process.hpp"
#include "Power.hpp"
#include "Misc.hpp"

struct ModuleDataBuffer
{
  Module::Processor::CPU::CPUGlobal CPU;
  Module::Network::NetworkGlobal    network;
  Module::System::SystemGlobal      sys;
  Module::Disk::DiskGlobal          disk;
  Module::RAM::RAMGlobal            ram;
  Module::Process::ProcessGlobal    proc;
  Module::Power::PowerGlobal        power;
  Module::Misc::MiscGlobal          misc;
};

#endif // !MODULEDATABUFFER_HPP_
