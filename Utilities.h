// Name: Le Minh Pham
// Seneca Student ID: 107259186
// Seneca email: lmpham1@myseneca.ca
// Date of completion: 15/11/2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>

	class Utilities {
		size_t m_widthField = 1;
		static char m_delimiter;
	public:
		void setFieldWidth(size_t);
		size_t getFieldWidth() const;
		const std::string extractToken(const std::string&, size_t&, bool&);
		static void setDelimiter(const char);
		const char getDelimiter() const;
	};
#endif