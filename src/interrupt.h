#ifndef INTERRUPT_H
#define INTERRUPT_H

////////////////////////////////////////////////////////////////////////////////
//
// Includes
//

// STD Includes
#include <string>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// class CInterrupt
//
class CInterrupt
{
public:// Native Types
	enum EInterrupt
	{
		EndProcess,

		LoadModule,

		Error,

		Default = Error
	};

public:// Constructor
	inline CInterrupt(EInterrupt eIterrupt = Default, std::string strMessage = "");
	~CInterrupt() = default;

public:// Interface Methodes
	inline EInterrupt GetInterrupt() const;
	inline std::string const& GetMessage() const;
	inline void SetMessage(std::string const strMessage);

private:// Members
	std::string m_strMessage;
	EInterrupt m_eIterrupt;
};
////////////////////////////////////////////////////////////////////////////////

///////////////////////// Implementing inline methods //////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CInterrupt
//
// Constructor
inline CInterrupt::CInterrupt(EInterrupt eIterrupt, std::string strMessage)
	: m_strMessage(strMessage),
	  m_eIterrupt(eIterrupt)
{

}

// Interface Methodes
inline CInterrupt::EInterrupt CInterrupt::GetInterrupt() const
{
	return m_eIterrupt;
}

inline std::string const& CInterrupt::GetMessage() const
{
	return m_strMessage;
}

inline void CInterrupt::SetMessage(std::string const strMessage)
{
	m_strMessage = strMessage;
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////


#endif // INTERRUPT_H