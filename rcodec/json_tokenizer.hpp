#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace rcodec {
	class json_tokenizer {
	public:
		enum class token_type {
			START_BRACE,
			END_BRACE,
			START_BRACKET,
			END_BRACKET,
			COLON,
			COMMA,
			PROPERTY,
			STRING,
			EOF
		};

		static const std::string& getName(token_type tokenType);

		struct token {
			const token_type type;
			const std::string buf;

			token(
				token_type tknType,
				const std::string& tknBuf) :
				type(tknType),
				buf(tknBuf) {}

			friend std::ostream& operator<<(std::ostream& os, const token& tkn);
		};

	private:
		std::istream * _in;
		std::unique_ptr<token> _readyToken;
		unsigned int _charLoc;
		unsigned int _lineLoc;

	public:
		json_tokenizer(std::istream & in) :
			_in(in),
			_readyToken(nullptr),
			_charLoc(0),
			_lineLoc(0) {}

		std::unique_ptr<token> nextToken();
			
	private:
		std::string finishQuote();		
	};

	std::ostream& operator<<(std::ostream& os, json_tokenizer::token_type tknType);	
}
