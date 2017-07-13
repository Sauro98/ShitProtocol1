#pragma once

#include "LoRaProtocol.h"


#define REGISTRATION_RESPONSE_ID_DENIED 0
#define REGISTRATION_RESPONSE_ID_ACCEPTED 1
#define REGISTRATION_RESPONSE_REGISTRATION_DENIED 2
#define REGISTRATION_RESPONSE_REGISTRATION_RESUMED 3

typedef struct Id_pn_pair {
	uint32_t ID = 0;
	uint8_t packetNumber = -1;

	Id_pn_pair(uint32_t _ID, uint8_t _packetNumber) {
		ID = _ID;
		packetNumber = _packetNumber;
	}

	Id_pn_pair() {
	}

	bool operator == (const Id_pn_pair& other) {
		return ID == other.ID && packetNumber == other.packetNumber;
	}

}Pair_p;

static Packet RegistrationPacket(uint32_t dest, uint32_t sender) {
	return Packet(dest, sender, PACKET_TYPE_NORM | PACKET_TYPE_REGISTRATION, packetCounter, "", 0);
}

static Packet RegistrationIDDeniedPacket(uint32_t dest, uint32_t sender) {
	char body[1];
	body[0] = REGISTRATION_RESPONSE_ID_DENIED;
	return Packet(dest, sender, PACKET_TYPE_NORM | PACKET_TYPE_REGISTRATION, packetCounter, body, 1);
}

static Packet RegistrationIDAcceptedPacket(uint32_t dest, uint32_t sender) {
	char body[1];
	body[0] = REGISTRATION_RESPONSE_ID_ACCEPTED;
	return Packet(dest, sender, PACKET_TYPE_NORM | PACKET_TYPE_REQUESTS_ACK | PACKET_TYPE_REGISTRATION, packetCounter, body, 1);
}

static Packet RegistrationResumedPacket(uint32_t dest, uint32_t sender) {
	char body[1];
	body[0] = REGISTRATION_RESPONSE_REGISTRATION_RESUMED;
	return Packet(dest, sender, PACKET_TYPE_NORM | PACKET_TYPE_REGISTRATION, packetCounter, body, 1);
}

static Packet RegistrationUnavailablePacket(uint32_t dest, uint32_t sender) {
	char body[1];
	body[0] = REGISTRATION_RESPONSE_REGISTRATION_DENIED;
	return Packet(dest, sender, PACKET_TYPE_NORM | PACKET_TYPE_REGISTRATION, packetCounter, body, 1);
}


static bool isRegistrationResponsePacket(uint8_t type, uint8_t packetLenght){
	return ((type & 126) == PACKET_TYPE_REGISTRATION) && packetLenght == 1;
}

static bool isRegistrationRequestPacket(uint8_t type, uint8_t packetLenght) {
	return ((type & 126) == PACKET_TYPE_REGISTRATION) && packetLenght == 0;
}

static int response_result(uint8_t payload) {
	return payload & 3;
}

static bool wasResent(Id_pn_pair one, Id_pn_pair two) {
	return one.ID == two.ID && one.packetNumber < two.packetNumber;
}