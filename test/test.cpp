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
    state->digitalPin[SS].addObserver("Ethernet", this);
  }

  ~BitCollector() { state->digitalPin[SS].removeObserver("Ethernet"); }

  virtual void onBit(bool aBit) {
    if (aBit) {
      int value = 0;
      value = (value << 1) + state->digitalPin[SS];
      value = (value << 1) + state->digitalPin[MOSI];
      value = (value << 1) + state->digitalPin[MISO];
      value = (value << 1) + state->digitalPin[SCK];
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

// print the output
// log the output
// check it

//   inline void setGatewayIp(const uint8_t * addr) { writeGAR(addr); }
unittest(GatewayIp)
{
  const uint8_t addr1[] = {192,168,0,1};
  uint8_t addr2[] = {0,0,0,0};
  BitCollector pinValues(true, false);
  W5100.setGatewayIp(addr1);
  // Look and see what values got sent to the collected pins
  W5100.getGatewayIp(addr2);

  assertEqual(192, addr2[0]);
  assertEqual(168, addr2[1]);
  assertEqual(0, addr2[2]);
  assertEqual(1, addr2[3]);
}


unittest_main()