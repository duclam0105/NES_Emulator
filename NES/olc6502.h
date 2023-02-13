#pragma once
#include <vector>
#include <string>
#include <map>
#include "Mylib.h"

class Bus;

// The 6502 Emulation Class
class olc6502
{
public:
	olc6502();
	~olc6502();

	void connectBus(Bus* n) { bus = n; }
public:
	//6052 Processor Status Reg "P" - Comment by LamND
	enum FLAGS6502 {
		C = (1 << 0),	//Carry bit
		Z = (1 << 1),	//Zero
		I = (1 << 2),	//Disable Interrupts	(IRQ Disable)
		D = (1 << 3),	//Decimal Mode (unused)
		B = (1 << 4),	//Break		(Break Command)
		U = (1 << 5),	//Unused
		V = (1 << 6),	//Overflow
		N = (1 << 7),	//Negative
	};

	//6052 Register - Comment by LamND
	uint8_t A = 0x00;		//Accumulator Reg
	uint8_t Y = 0x00;		//Y Index Reg
	uint8_t X = 0x00;		//X Index Reg
	uint16_t PC = 0x0000;	//Program Counter Reg (bit0-7: PCL | bit8-15: PCH)
	uint8_t STKP = 0x00;	//Stack Pointer Reg
	uint8_t status = 0x00;	//Status Reg

private:
	//6052 Addressing Modes - Comment by LamND
	uint8_t IMP();	uint8_t IMM();
	uint8_t ZP0();	uint8_t ZPX();
	uint8_t ZPY();	uint8_t REL();
	uint8_t ABS();	uint8_t ABX();
	uint8_t ABY();	uint8_t IND();
	uint8_t IZX();	uint8_t IZY();
	//6052 56 Opcodes - Comment by LamND
	uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
	uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
	uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
	uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
	uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
	uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
	uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
	uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
	uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
	uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
	uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
	uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
	uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

	// I capture all "unofficial" opcodes with this function. It is
	// functionally identical to a NOP
	uint8_t XXX();

	// 6052 Hardware Signals (External event) - Comment by LamND
	bool complete();
	void clock();	//Clock - Perform one clock cycle's worth of update
	void reset();	//Reset signal (When press Reset button) - Forces CPU into known state
	void irq();		//Interrupts - Executes an instruction at a specific location
	void nmi();		//Non-Maskable Interrupts - Ditto, but cannot be disabled
	
	// Assisstive variables to facilitate emulation
	uint8_t  fetched = 0x00;	// Represents the working input value to the ALU
	uint16_t temp = 0x0000;		// A convenience variable used everywhere
	uint16_t addr_abs = 0x0000; // All used memory addresses end up in here
	uint16_t addr_rel = 0x00;   // Represents absolute address following a branch
	uint8_t  opcode = 0x00;		// Is the instruction byte
	uint8_t  cycles = 0;		// Counts how many cycles the instruction has remaining
	uint32_t clock_count = 0;	// A global accumulation of the number of clocks

	uint8_t fetch();
private:
	Bus* bus = nullptr;
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t data);

	//Convenience functions to access status register
	uint8_t getFlag(FLAGS6502 flag);
	void setFlag(FLAGS6502 flag, bool v);
	// One instruction include name (opcode), operator, addrmode, cycles
	// Using funtion pointer to call opcode
	
	struct INSTRUCTION
	{
		string name;	
		uint8_t(olc6502::* operate)(void) = nullptr;
		uint8_t(olc6502::* addrmode)(void) = nullptr;
		uint8_t cycles = 0;
	};
	
	vector<INSTRUCTION> lookupTable;
};

