#define EthernetClass_Test EthernetClass_CI
#include "Common.cpp"

unittest(testingClassName) {
  EthernetClass_Test Ethernet;
  assertEqual("EthernetClass_CI", Ethernet.className());
}

unittest(localIP_high) {
    EthernetClass_Test testClass;
    IPAddress expected(192,168,1,1);
    testClass.setLocalIP(expected);
    IPAddress result = testClass.localIP();
    assertEqual(expected, result);
}

unittest(subnetMask_high) {
    EthernetClass_Test testClass;
    IPAddress expected(192,168,1,1);
    testClass.setSubnetMask(expected);
    IPAddress result = testClass.subnetMask();
    assertEqual(expected, result);
}

unittest(gatewayIP_high) {
    EthernetClass_Test testClass;
    IPAddress expected(192,168,1,1);
    testClass.setGatewayIP(expected);
    IPAddress result = testClass.gatewayIP();
    assertEqual(expected, result);
}

unittest_main()