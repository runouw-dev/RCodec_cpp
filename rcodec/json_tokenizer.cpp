#include "json_tokenizer.hpp"

#include <cstddef>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "json_utils.hpp"

namespace rcodec {
	namespace {
		static const std::string _ID_START_BRACE = "{";
		static const std::string _ID_END_BRACE = "}";
		static const std::string _ID_START_BRACKET = "[";
		static const std::string _ID_END_BRACKET = "]";
		static const std::string _ID_COLON = ":";
		static const std::string _ID_COMMA = ",";
		static const std::string _ID_PROPERTY = "property";
		static const std::string _ID_STRING = "string";
		static const std::string _ID_EOF = "EOF";

		static json_tokenizer::token __makeToken(
			json_tokenizer::token_type tokenType) {

			return json_tokenizer::token(
				tokenType,
				json_tokenizer::getName(tokenType));
		}

		static json_tokenizer::token __makeToken(
			json_tokenizer::token_type tokenType,
			const std::string& buff) {

			return json_tokenizer::token(tokenType, buff);
		}

		static void __assign(
			std::unique_ptr<json_tokenizer::token>& ptr,
			json_tokenizer::token&& value) {

			auto newPtr = std::make_unique<json_tokenizer::token> (value);

			std::swap(ptr, newPtr);
		}

		static std::unique_ptr<json_tokenizer::token> __steal(
			std::unique_ptr<json_tokenizer::token>& ptr) {

			std::unique_ptr<json_tokenizer::token> newPtr(nullptr);

			std::swap(ptr, newPtr);

			return newPtr;
		}
	}

	const std::string& json_tokenizer::getName(json_tokenizer::token_type tokenType) {
		using tkn_t = json_tokenizer::token_type;

		switch (tokenType) {
			case tkn_t::START_BRACE:
				return _ID_START_BRACE;
			case tkn_t::END_BRACE:
				return _ID_END_BRACE;
			case tkn_t::START_BRACKET:
				return _ID_START_BRACKET;	
			case tkn_t::END_BRACKET:
				return _ID_END_BRACKET;	
			case tkn_t::COLON:
				return _ID_COLON;
			case tkn_t::COMMA:
				return _ID_COMMA;
			case tkn_t::PROPERTY:
				return _ID_PROPERTY;
			case tkn_t::STRING:
				return _ID_STRING;
			case tkn::EOF:
				return _ID_EOF;
			default:
				std::cerr << "Unknown token type!" << std::endl;
				__builtin_trap();
		}
	}

	std::ostream& operator<<(std::ostream& os, json_tokenizer::token_type tknType) {
		return os << "Token "
			<< json_tokenizer::getName(tknType);		
	}

	std::ostream& operator<<(std::ostream& os, const json_tokenizer::token& tkn) {
		return os << "Token["
			<< getName(tkn.type)
			<< ", "
			<< tkn.buf
			<< "]";				
	}

	void json_tokenizer::finishQuote() {
		std::stringstream buff;
		char last = '\0';

		while (true) {
			int read = _in.get();
			_charLoc++;

			if (read == -1) {
				throw "End of File reached!";
			}

			auto c = static_cast<char> (read);

			if (c == '\n') {
				_charLoc = 0;
				_lineLoc++;
			}

			if (c == '"' && last != '\\') {
				return json_utils::restoreString(buff.str());
			}

			last = c;
			buff << c;
		}		
	}	

	std::unique_ptr<json_tokenizer::token> json_tokenizer::nextToken() {
		if (_readyToken != nullptr) {
			return __steal(_readyToken);
		}

		std::stringstream buff;
		std::size_t buffLen = 0;

		while (true) {
			int read = _in.get();
			_charLoc++;

			if (read == -1) {
				__assign(_readyToken, __makeToken(token_type::EOF));
			}

			auto c = static_cast<char> (read);

			switch (c) {
				case '{':
					__assign(_readyToken, __makeToken(token_type::START_BRACE));
					break;
				case '}':
					__assign(_readyToken, __makeToken(token_type::END_BRACE));
					break;
				case '[':
					__assign(_readyToken, __makeToken(token_type::START_BRACKET));
					break;
				case ']':
					__assign(_readyToken, __makeToken(token_type::END_BRACKET));
					break;
				case ':':
					__assign(_readyToken, __makeToken(token_type::COLON));
					break;
				case ',':
					__assign(_readyToken, __makeToken(token_type::COMMA));
					break;
				case '"':
					__assign(_readyToken, __makeToken(token_type::STRING, finishQuote());
					break;
				case ' ':
				case '\t':					
				case '\r':
					break;
				case '\n':
					charLoc = 0;
					lineLoc++;
					break;
				default:
					buffLen++;
					buff << c;
					break;
			}

			if (readyToken != nullptr) {
				if (buffLen > 0) {
					return std::make_unique<token> (token_type::PROPERTY, buff.str());
				} else {
					return __steal(_readyToken);
				}
			}
		}
	}
}
