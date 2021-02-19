
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

template <typename PacketStream>
class PacketReader {
public:
	void ReadPacket(PacketStream* stream, size_t packet_num) {
		printf("PacketReader - ReadPacket\n");
		stream->AppendPacket(nullptr);
		stream->GetPacket(packet_num);
	}
};

int main() {
	ConcreatePacketStream stream;
	PacketReader<ConcreatePacketStream> reader;

	reader.ReadPacket(&stream, 42);
}
