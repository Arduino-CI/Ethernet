#include <Ethernet_CI.h>
#ifdef MOCK_PINS_COUNT

int EthernetClass_CI::begin(uint8_t *mac, unsigned long timeout = 60000, unsigned long responseTimeout = 4000) {
    _mac = mac;
    _timeout = timeout;
    _responseTimeout = responseTimeout;
    return EthernetClass_Base::begin(mac, timeout, responseTimeout);
}

// look in ethernet.cpp for the DHCP values
int maintain() {
    return EthernetClass_Base::maintain();
}

EthernetLinkStatus linkStatus() {
    return EthernetClass_Base::linkStatus();
}

EthernetHardwareStatus hardwareStatus() {
    return EthernetClass_Base::hardwareStatus();
}


void EthernetClass_CI::begin(uint8_t *mac, IPAddress ip) {
	IPAddress dns = ip;
	dns[3] = 1;
	begin(mac, ip, dns);
}

void EthernetClass_CI::begin(uint8_t *mac, IPAddress ip, IPAddress dns) {
	IPAddress gateway = ip;
	gateway[3] = 1;
	begin(mac, ip, dns, gateway);
}

void EthernetClass_CI::begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway) {
	IPAddress subnet(255, 255, 255, 0);
	begin(mac, ip, dns, gateway, subnet);
}

void EthernetClass_CI::begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet) {
    _mac = mac;
    _ip = ip;
    _dns = dns;
    _gateway = gateway;
    _subnet = subnet;
    EthernetClass_Base::begin(mac, ip, dns, gateway, subnet);
}

void EthernetClass_CI::init(uint8_t sspin = 10) {
    _sspin = sspin;
    EthernetClass_Base::init(sspin);
}

// Talk to foster!!!!!
void MACAddress(uint8_t *mac_address) {
    *mac_address = *_mac;
}

IPAddress EthernetClass_CI::localIP() {
    return _ip;
}

IPAddress EthernetClass_CI::subnetMask() {
    return _subnet;
}

IPAddress EthernetClass_CI::gatewayIP() {
    return _gateway;
}

void EthernetClass_CI::setMACAddress(const uint8_t *mac_address) {
    *_mac = *mac_address;
    EthernetClass_Base::setMACAddress(mac_address);
}

void EthernetClass_CI::setLocalIP(const IPAddress local_ip) {
    _ip = local_ip;
    EthernetClass_Base::setLocalIP(local_ip);
}

void EthernetClass_CI::setSubnetMask(const IPAddress subnet) {
    _subnet = subnet;
    EthernetClass_Base::setSubnetMask(subnet);
}

void EthernetClass_CI::setGatewayIP(const IPAddress gateway) {
    _gateway = gateway;
    EthernetClass_Base::setGatewayIP(gateway);
}

void EthernetClass_CI::setRetransmissionTimeout(uint16_t milliseconds) {
    _retransmissionTimeout = milliseconds;
    EthernetClass_Base::setRetransmissionTimeout(milliseconds);
}

void EthernetClass_CI::setRetransmissionCount(uint8_t num) {
    _retransmissionCount = num;
    EthernetClass_Base::setRetransmissionCount(num);
}

// Instances
IPAddress EthernetClass_CI::_dnsServerAddress;
DhcpClass* EthernetClass_CI::_dhcp = NULL;

uint8_t *EthernetClass_CI::_mac;
unsigned long EthernetClass_CI::_timeout;
unsigned long EthernetClass_CI::_responseTimeout;
IPAddress EthernetClass_CI::_ip;
IPAddress EthernetClass_CI::_dns;
IPAddress EthernetClass_CI::_gateway;
IPAddress EthernetClass_CI::_subnet;
uint8_t *EthernetClass_CI::_mac_address;
IPAddress EthernetClass_CI::_local_ip;
uint8_t EthernetClass_CI::_sspin;
uint16_t EthernetClass_CI::_retransmissionTimeout;
uint8_t EthernetClass_CI::_retransmissionCount;

EthernetClass_CI Ethernet;

#endif
