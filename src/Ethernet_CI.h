#pragma once
#include <Ethernet.h>
#ifdef MOCK_PINS_COUNT

class EthernetUDP;
class EthernetClient;
class EthernetServer;
class DhcpClass;

class EthernetClass_CI : public EthernetClass_Base {
public:
	// Initialise the Ethernet shield to use the provided MAC address and
	// gain the rest of the configuration through DHCP.
	// Returns 0 if the DHCP configuration failed, and 1 if it succeeded
	static int begin(uint8_t *mac, unsigned long timeout = 60000, unsigned long responseTimeout = 4000);
	static int maintain();
	static EthernetLinkStatus linkStatus();
	static EthernetHardwareStatus hardwareStatus();

	// Manual configuration
	static void begin(uint8_t *mac, IPAddress ip);
	static void begin(uint8_t *mac, IPAddress ip, IPAddress dns);
	static void begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway);
	static void begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet);
	static void init(uint8_t sspin = 10);

	static void MACAddress(uint8_t *mac_address);
	static IPAddress localIP();
	static IPAddress subnetMask();
	static IPAddress gatewayIP();
	static IPAddress dnsServerIP() { return _dnsServerAddress; }
	static uint16_t getRetransmissionTimeout() { return _retransmissionTimeout; }
	static uint8_t getRetransmissionCount() {return _retransmissionCount; }

	void setMACAddress(const uint8_t *mac_address);
	void setLocalIP(const IPAddress local_ip);
	void setSubnetMask(const IPAddress subnet);
	void setGatewayIP(const IPAddress gateway);
	void setDnsServerIP(const IPAddress dns_server) { _dnsServerAddress = dns_server; }
	void setRetransmissionTimeout(uint16_t milliseconds);
	void setRetransmissionCount(uint8_t num);

	virtual String className() const { return "EthernetClass_CI"; }

	// friend class EthernetClient;
	// friend class EthernetServer;
	// friend class EthernetUDP;
private:
	static IPAddress _dnsServerAddress;
	static DhcpClass* _dhcp;

	// custom testing
	static uint8_t *_mac;
	static unsigned long _timeout;
	static unsigned long _responseTimeout;
	static IPAddress _ip;
	static IPAddress _dns;
	static IPAddress _gateway;
	static IPAddress _subnet;
	static uint8_t *_mac_address;
	static IPAddress _local_ip;
	static uint8_t _sspin;
	static uint16_t _retransmissionTimeout;
	static uint8_t _retransmissionCount;
};

extern EthernetClass_CI Ethernet;


#endif
