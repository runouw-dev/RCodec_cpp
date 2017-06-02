#pragma once

namespace rcodec {
	class coder_array;

	struct codable_array_decode {
		virtual void decode(coder_array& decoder) = 0;
	};
}
