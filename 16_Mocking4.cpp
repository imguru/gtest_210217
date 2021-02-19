
// 16_Mocking4.cpp
//  C++ 에서는 Template을 기반으로 동일한 설계를 작성할 수 있습니다.
//   => Policy based design(단위 전략)

#include <stdio.h>

struct Packet {};

class ConcreatePacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatePacketStream - AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {
		printf("ConcreatePacketStream - GetPacket\n");
		return nullptr;
	}
};

// 정책 클래스를 실행 시간에 교체할 필요가 없을 경우 사용한다.
template <typename PacketStream>
class PacketReader {
public:
	void ReadPacket(PacketStream* stream, size_t packet_num) {
		printf("PacketReader - ReadPacket\n");
		stream->AppendPacket(nullptr);
		// stream->GetPacket(packet_num);
	}
};

#if 0
int main() {
	ConcreatePacketStream stream;
	PacketReader<ConcreatePacketStream> reader;

	reader.ReadPacket(&stream, 42);
}
#endif


//--------------
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#if 0
class ConcreatePacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatePacketStream - AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {
		printf("ConcreatePacketStream - GetPacket\n");
		return nullptr;
	}
};
#endif

class MockPacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
};

TEST(PacketReaderTest, ReadPacket) {
	MockPacketStream mock;
	PacketReader<MockPacketStream> reader; // !!!!

	EXPECT_CALL(mock, AppendPacket(nullptr));
	EXPECT_CALL(mock, GetPacket(42));

	reader.ReadPacket(&mock, 42);
}
