#ifndef MODULEDATABUFFER_HPP_
#define MODULEDATABUFFER_HPP_

// This module describes the ModuleDataBuffer which contains every information
// collected by the data miner threads

#include "CPU.hpp"
#include "Network.hpp"
#include "System.hpp"
#include "Disk.hpp"

struct ModuleDataBuffer
{
  Module::Processor::CPU::CPUGlobal CPU;
  Module::Network::NetworkGlobal    network;
  Module::System::SystemGlobal	sys;
  Module::Disk::DiskGlobal disk;
};

#endif // !MODULEDATABUFFER_HPP_
