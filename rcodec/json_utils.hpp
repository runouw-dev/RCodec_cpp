#pragma once

#include <string>

namespace rcodec {
	namespace json_utils {
		std::string cleanString(const std::string& str);

		std::string restoreString(const std::string& str);
	}
}
