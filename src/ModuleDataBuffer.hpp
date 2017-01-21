#ifndef MODULEDATABUFFER_HPP_
#define MODULEDATABUFFER_HPP_

// This module describes the ModuleDataBuffer which contains every information
// collected by the data miner threads

#include "CPU.hpp"

struct ModuleDataBuffer
{
  Module::Processor::CPU::CPUGlobal CPU;
};

#endif // !MODULEDATABUFFER_HPP_
