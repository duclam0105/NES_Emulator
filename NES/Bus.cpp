#include "Bus.h"


Bus::Bus() {
	//Reset RAM contents
	for (auto& i : ram) {
		i = 0x00;
	}
	//Connect CPU to communication bus
	cpu.connectBus(this);
}

Bus::~Bus() {
}

void Bus::writeBus(uint16_t addr, uint8_t data) {
	if (addr >= 0x0000 && addr <= MAX_RAM) {
		ram[addr] = data;
	}
}
uint8_t Bus::readBus(uint16_t addr, bool bReadOnly) {
	if (addr >= 0x0000 && addr <= MAX_RAM) {
		return ram[addr];
	}
	return 0x0000;
}