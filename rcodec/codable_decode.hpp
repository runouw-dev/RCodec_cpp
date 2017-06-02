#pragma once

namespace rcodec {
	class coder_node;

	struct codable_decode {
		virtual void decode(coder_node& decoder) = 0;
	};
}
