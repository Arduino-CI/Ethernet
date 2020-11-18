#define EthernetClass_Test EthernetClass_Base
#include "Common.cpp"

unittest(testingClassName) {
  EthernetClass_Test Ethernet;
  assertEqual("EthernetClass_Base", Ethernet.className());
}

unittest_main()
