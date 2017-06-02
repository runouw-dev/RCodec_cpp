#pragma once

#include <cstdint>

#include <string>

namespace rcodec {
	struct byte_writer {
		virtual byte_writer& writeHeader() = 0;

		virtual byte_writer& write(std::int8_t value) = 0;

		virtual byte_writer& write(std::size_t len, const std::int8_t * data) = 0;

		virtual byte_writer& writeString(const std::string& str) = 0;

		virtual byte_writer& writeBool(bool value) = 0;

		virtual byte_writer& writeShort(std::int16_t value) = 0;

		virtual byte_writer& writeInt(std::int32_t value) = 0;

		virtual byte_writer& writeFloat(float value) = 0;

		virtual byte_writer& writeDouble(double value) = 0;
	};
}
