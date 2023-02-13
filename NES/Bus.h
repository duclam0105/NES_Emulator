#pragma once
#include <cstdint>
#include <array>
#include "Mylib.h"
#include "olc6502.h"

class Bus
{
public:
	Bus();
	~Bus();
	
	//Devices on bus
	olc6502 cpu;
	//Fake RAM
	array<uint8_t, 64 * 1024> ram;

	//Read vs Write Bus
	void writeBus(uint16_t addr, uint8_t data);
	uint8_t readBus(uint16_t addr, bool bReadOnly = false);
};

