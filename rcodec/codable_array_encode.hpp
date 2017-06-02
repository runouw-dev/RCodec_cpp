#pragma once

namespace rcodec {
	class coder_array;

	struct codable_array_encode {
		virtual coder_array& encode(coder_array& encoder) = 0;
	};
}
