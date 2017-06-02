#pragma once

#include <cstdint>

#include <string>

namespace rcodec {
	struct byte_reader {
		virtual bool readBool() = 0;

		virtual std::int8_t readByte() = 0;

		virtual std::int16_t readShort() = 0;

		virtual std::int32_t readInt() = 0;

		virtual std::int64_t readLong() = 0;

		virtual float readFloat() = 0;

		virtual double readDouble() = 0;

		virtual std::string readString() = 0;

		virtual bool checkHeader() = 0;

		virtual std::int8_t * readBytes(std::size_t length, std::int8_t * data) = 0;
	};
}
