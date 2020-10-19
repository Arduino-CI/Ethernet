#include <bitset>
#include <iostream>
#include <vector>

#include "Arduino.h"
#include "ArduinoUnitTests.h"
#include "ci/ObservableDataStream.h"
#include "Ethernet.h"
#include "utility/w5100.h"

// make the bit collector class
const byte SS   = 10;
const byte MOSI = 11;
const byte MISO = 12;
const byte SCK  = 13;

class BitCollector : public DataStreamObserver {
private:
  bool fourBitMode;
  bool showData;
  vector<int> pinLog;
  GodmodeState *state;

public:
  BitCollector(bool showData = false, bool fourBitMode = true)
      : DataStreamObserver(false, false) {
    this->fourBitMode = fourBitMode;
    this->showData = showData;
    state = GODMODE();
    state->reset();
    state->digitalPin[MOSI].addObserver("Ethernet", this);
  }

  ~BitCollector() { state->digitalPin[MOSI].removeObserver("Ethernet"); }

  virtual void onBit(bool aBit) {
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
        if (fourBitMode) {
          std::bitset<4> bits((value >> 4) & 0x0F);
          if ((pinLog.size() - 1) % 2) {
            std::cout << "    ";
          }
          std::cout << bits;
        } else {
          std::bitset<8> bits(value & 0xFF);
          std::cout << bits;
        }
        std::cout << std::endl;
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

// Read the output off the Ethernet.begin() method
unittest(test_EthernetBegin) 
{
  uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

  BitCollector pinValues(true, false);
  Ethernet.begin(mac);
  std::cout << "Helloworld" << std::endl;
}

unittest_main()