#pragma once

namespace rcodec {
	class coder_node;

	struct codable_encode {
		virtual coder_node& encode(coder_node& encoder) = 0;		
	};
}
