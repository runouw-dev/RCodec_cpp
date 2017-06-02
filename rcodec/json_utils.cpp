#include "json_utils.hpp"

#include <sstream>
#include <string>

namespace rcodec {
	namespace json_utils {
		std::string cleanString(const std::string& str) {
			std::stringstream newStr;

			for (auto c : str) {
				switch (c) {
					case '\\':
					case '"':
						newStr << '\\' << c;
						break;
					case '\n':
						newStr << '\\' << 'n';
						break
					case '\t':
						newStr << '\\' << 't';
						break;
					case '\r':
						newStr << '\\' << 'r';
						break;
					default:
						newStr << c;
						break;
				}
			}

			return newStr.str();
		}

		std::string restoreString(const std::string& str) {
			std::stringstream newStr;

			for (std::size_t i = 0; i < str.size(); i++) {
				auto c = str[i];
				auto next = ((i + 1) >= str.size()) ? '\0' : (str[i + 1]);

				switch (c) {
					case '\n':
					case '\t':
					case '\r':
						break;
					case '\\':
						switch (next) {
							case 't':
								newStr << '\t';
								i++;
								break;
							case 'n':
								newStr << '\n';
								i++;
								break;
							case 'r':
								newStr << '\r';
								i++;
								break;
							default:
								newStr << next;
								i++;
								break;
						}

						break;
					default:
						newStr << c;
						break;
				}
			}

			return newStr.str();			
		}
	}
}
