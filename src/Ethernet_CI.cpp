#include <Ethernet_CI.h>
#ifdef MOCK_PINS_COUNT_X

int EthernetClass_CI::begin(uint8_t *mac, unsigned long timeout = 60000, unsigned long responseTimeout = 4000) {
    return EthernetClass_Base::begin(mac, timeout, responseTimeout);
}

// static int maintain();
// static EthernetLinkStatus linkStatus();
// static EthernetHardwareStatus hardwareStatus();

// // Manaul configuration
// static void begin(uint8_t *mac, IPAddress ip);
// static void begin(uint8_t *mac, IPAddress ip, IPAddress dns);
// static void begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway);
// static void begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet);
// static void init(uint8_t sspin = 10);

// static void MACAddress(uint8_t *mac_address);
// static IPAddress localIP();
// static IPAddress subnetMask();
// static IPAddress gatewayIP();
// static IPAddress dnsServerIP() { return _dnsServerAddress; }

// void setMACAddress(const uint8_t *mac_address);
// void setLocalIP(const IPAddress local_ip);
// void setSubnetMask(const IPAddress subnet);
// void setGatewayIP(const IPAddress gateway);
// void setDnsServerIP(const IPAddress dns_server) { _dnsServerAddress = dns_server; }
// void setRetransmissionTimeout(uint16_t milliseconds);
// void setRetransmissionCount(uint8_t num);

#endif