#pragma once

#include "codable_encoder.hpp"
#include "codable_decoder.hpp"

namespace rcodec {
	struct codable : public codable_encoder, public codable_decoder {
		
	};
};
