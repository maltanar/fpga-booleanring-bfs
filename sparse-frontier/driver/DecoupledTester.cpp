#include <assert.h>
#include <iostream>
#include "DecoupledTester.h"

DecoupledTester::DecoupledTester(unsigned int baseAddr, bool is64Bit) {

	m_inputRegs = (volatile unsigned int *) baseAddr;
	m_outputRegs = (volatile unsigned int *) (baseAddr + BASE_OUTPUT_OFFSET);
	m_fifoWriteCount = 0;
	m_fifoReadCount = 0;

	m_is64Bit = is64Bit;

	// self test: check that we can read the constant ID from the inputs regs

	if (m_inputRegs[15] != 1234567) {
		std::cout << "Error reading ID from DecoupledTester input regs!"
				<< std::endl;
		std::cout << "Found: " << m_inputRegs[15] << std::endl;
		return;
	}

	// check the loopback from output to input to ensure outputregs work correctly
	m_outputRegs[15] = 0xdeadbeef;

	if (m_inputRegs[14] != 0xdeadbeef) {
		std::cout << "Error with loopback from DecoupledTester regs!"
				<< std::endl;
		std::cout << "Found: " << m_inputRegs[14] << std::endl;
		return;
	}
}

DecoupledTester::~DecoupledTester() {
	// TODO Auto-generated destructor stub
}

unsigned int DecoupledTester::getInputFIFODataCount() {
	return m_inputRegs[regInputFIFODataCount];
}

unsigned int DecoupledTester::getOutputFIFODataCount() {
	return m_inputRegs[regOutputFIFODataCount];
}

bool DecoupledTester::writeToSingle(unsigned int value) {
	// check whether writes can proceed
	if (m_inputRegs[regInFIFOWriteReady] != 1) {
		return false;
	}

	// expose input data to FIFO
	m_outputRegs[regOutFIFOWriteData] = value;
	// create pulse by writing new write count
	m_fifoWriteCount++;
	// PulseGenerator generates a 1-cycle pulse when the input changes
	m_outputRegs[regOutFIFOWritePulse] = m_fifoWriteCount;

	return true;
}

bool DecoupledTester::readFromSingle(unsigned int & value) {
	// check whether reads can proceed
	if (m_inputRegs[regInFIFOReadDataAvailable] != 1)
		return false;

	// data readout
	value = m_inputRegs[regInFIFOReadDataUpper32];

	// increment read count and use for pulse generation
	m_fifoReadCount++;
	m_outputRegs[regOutFIFOReadPulse] = m_fifoReadCount;

	return true;
}

bool DecoupledTester::readFromDouble(unsigned int& valueUpper,
		unsigned int& valueLower) {
	// check whether reads can proceed
	if (m_inputRegs[regInFIFOReadDataAvailable] != 1)
		return false;

	// data readout
	valueUpper = m_inputRegs[regInFIFOReadDataUpper32];
	valueLower = m_inputRegs[regInFIFOReadDataLower32];

	// increment read count and use for pulse generation
	m_fifoReadCount++;
	m_outputRegs[regOutFIFOReadPulse] = m_fifoReadCount;

	return true;
}

void DecoupledTester::passthrough(unsigned int count, bool print) {
	unsigned int val = 0;
	while (readFromSingle(val) && count > 0) {
		if (print)
			std::cout << "Passthrough: " << val << std::endl;
		writeToSingle(val);
		count--;
	}
}

void DecoupledTester::readAndPrintAll(bool dbl) {

	std::cout << "Input FIFO dump: " << std::endl;
	if (dbl) {
		unsigned int val1, val2;
		while (readFromDouble(val1, val2)) {
			std::cout << "Read: " << val1 << " " << val2 << std::endl;
		}
	} else {

	}
	unsigned int val;
	while (readFromSingle(val)) {
		std::cout << "Read: " << val << "(0x" << std::hex << val << std::dec << ")" << std::endl;
	}
}
