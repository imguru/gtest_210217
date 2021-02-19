
#include <stdio.h>

struct Packet {};

struct PacketStream {
	virtual ~PacketStream() {}

	virtual void AppendPacket(Packet* new_packet) = 0;
	virtual const Packet* GetPacket(size_t packet_number) const = 0;
};

class ConcreatePacketStream : public PacketStream {
public:
	void AppendPacket(Packet* new_packet) override {
		printf("ConcreatePacketStream - AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const override {
		return nullptr;
	}
};

class PacketReader {
public:
	void ReadPacket(PacketStream* stream, size_t packet_num) {
		printf("PacketReader - ReadPacket\n");
		// stream->AppendPacket(nullptr);
		// stream->GetPacket(packet_num);
	}
};

//-------------------
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockPacketStream : public PacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet), (override));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const, override));
};

// PacketReader라는 SUT의 ReadPacket을 호출하였을 때, stream을 대상으로 AppendPacket / GetPacket이 제대로 호출되는지 여부를
// 검증하고 싶다.
TEST(PacketReaderTest, ReadPacket) {
	MockPacketStream mock;
	PacketReader reader;

	EXPECT_CALL(mock, AppendPacket(nullptr));
	EXPECT_CALL(mock, GetPacket(42));

	reader.ReadPacket(&mock, 42);
}
