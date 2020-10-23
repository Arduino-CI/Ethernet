#include <bitset>
#include <iostream>
#include <vector>

#include "Arduino.h"
#include "ArduinoUnitTests.h"
#include "Ethernet.h"
#include "ci/ObservableDataStream.h"
#include "utility/w5100.h"

// make the bit collector class
const byte SS = 10;
const byte MOSI = 11;
const byte MISO = 12;
const byte SCK = 13;

class BitCollector : public DataStreamObserver {
private:
  bool fourBitMode;
  bool showData;
  vector<int> pinLog;
  GodmodeState *state;

public:
  BitCollector(bool showData = false) : DataStreamObserver(false, false) {
    this->showData = showData;
    state = GODMODE();
    state->reset();
    state->digitalPin[SCK].addObserver("Ethernet", this);
  }

  ~BitCollector() { state->digitalPin[SCK].removeObserver("Ethernet"); }

  virtual void onBit(bool aBit) {
    std::cout << "onBit(" << (int)aBit << ")" << std::endl;
    if (aBit) {
      int value = 0;
      value = (value << 1) + state->digitalPin[SS];
      value = (value << 1) + state->digitalPin[MOSI];
      value = (value << 1) + state->digitalPin[MISO];
      pinLog.push_back(value);
      if (showData) {
        std::cout.width(5);
        std::cout << std::right << value << " : " << ((value >> 9) & 1) << "  "
                  << ((value >> 8) & 1) << "  ";
        // if (fourBitMode) {
        //   std::bitset<4> bits((value >> 4) & 0x0F);
        //   if ((pinLog.size() - 1) % 2) {
        //     std::cout << "    ";
        //   }
        //   std::cout << bits;
        // } else {
        //   std::bitset<8> bits(value & 0xFF);
        //   std::cout << bits;
        // }
        // std::cout << std::endl;
      }
    }
  }

  bool isEqualTo(const vector<int> &expected) {
    if (pinLog.size() != expected.size()) {
      return false;
    }
    for (int i = 0; i < pinLog.size(); ++i) {
      if (pinLog.at(i) != expected.at(i)) {
        return false;
      }
    }
    return true;
  }

  virtual String observerName() const { return "BitCollector"; }
};

// Test the Ethernet.begin() behaves the same as it did in the simulators
unittest(test_EthernetBegin) {
  // Setup
  GodmodeState *state = GODMODE();
  state->reset();
  uint8_t mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  Ethernet.begin(mac);

  // Tests
  int expected[] = {0,    0,  -128, 1, -128, 0,   0, 0, 1,  0,  0,    0, -128,
                    1,    8,  0,    0, 0,    1,   0, 0, 0,  4,  -128, 0, 0,
                    0,    0,  0,    0, 4,    8,   0, 0, 0,  0,  -16,  0, 0,
                    -128, 15, 0,    0, 0,    -16, 0, 0, 16, 15, 0,    0, 0};  
  assertEqual(52, state->spi.dataOut.size());
  bool passed = true;
  for (int i = 0; i < 52; i++) {
    if (expected[i] != (int)state->spi.dataOut.at(i)) {
      passed = false;
      break;
    }
  }
  assertTrue(passed);
}

unittest_main()