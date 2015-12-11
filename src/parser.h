#ifndef PARSER_H
#define PARSER_H

////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#ifndef OPERATIONS_H
#	include "operations.h"
#endif

// STD Includes
#include <string>
#include <memory>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////
namespace parser {
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// class CParser
//
class CParser
{
public:// Constructors
	inline CParser() = default;
	inline ~CParser() = default;

public:// Interface Methodes
	std::shared_ptr<char> Parse(std::string const& strFilePath);

private:// Helper Functions


};
////////////////////////////////////////////////////////////////////////////////

///////////////////////// Implementing inline methods //////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CParser
//

// Constructors


// Interface Methodes


////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace parser
////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////


#endif // PARSER_H