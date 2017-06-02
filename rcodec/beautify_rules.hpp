#pragma once

namespace rcodec {
	enum class indentation {
		TABS,
		SPACES,
		MINIFIED
	}

	class beautify_rules {
	private:
		const indentation _indentation;
		const unsigned int _spacing;
		const unsigned int _arrayWrappingLength;

	public:
		constexpr beautify_rules(
			const indentation indentation = indentation::SPACES,
			const unsigned int spacing = 2,
			const unsigned int arrayWrappingLength) :
			_indentation(indentation),
			_space(spacing),
			_arrayWrappingLength(arrayWrappingLength) {}

		constexpr beautify_rules withIndentation(const indentation) const {
			return beautify_rules(indentation, _spacing, _arrayWrappingLength);
		}

		constexpr beautify_rules withSpacing(const unsigned int spacing) const {
			return beautify_rules(_indentation, spacing, _arrayWrappingLength);
		}

		constexpr beautify_rules withArrayWrappingLength(const unsigned int arrayWrappingLength) const {
			return beautify_rules(_indentation, _spacing, arrayWrappingLength);
		}

		constexpr indentation getIndentation() const {
			return _indentation;
		}

		constexpr unsigned int getSpacing() const {
			return _spacing;
		}

		constexpr unsigned int getArrayWrappingLength() const {
			return _arrayWrappingLength;
		}
	};	
}
