#ifndef STACK_H
#define STACK_H

////////////////////////////////////////////////////////////////////////////////
//
// Includes
//

// STD Includes
#include <memory>
#include <vector>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// class CStack
//
class CStack
{
public:// Constructors
	inline CStack(int nSize = 0);
	inline ~CStack() = default;

public:// Interface Methodes
	inline int GetSize();
	inline int& SP();
	inline int Top();
	inline void Push(int nValue);
	inline int Pop();

	int operator[](int nOffset) const;
	int& operator[](int nOffset);

private:// Members
	std::vector<int> m_arrMemory;
	int m_nSP;
};
////////////////////////////////////////////////////////////////////////////////

///////////////////////// Implementing inline methods //////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CStack
//

// Constructors
inline CStack::CStack(int nSize)
	: m_arrMemory(nSize),
	  m_nSP(0)
{
}

// Interface Methodes
inline int CStack::GetSize()
{
	return m_arrMemory.size();
}

inline int& CStack::SP()
{
	return m_nSP;
}

inline int CStack::Top()
{
	return m_arrMemory[m_nSP];
}

inline void CStack::Push(int nValue)
{
	if (m_nSP != m_arrMemory.size())
	{
		m_arrMemory[m_nSP] = nValue;
		++m_nSP;
	}
	else
	{
		// interrupt
		--m_nSP;
	}
}

inline int CStack::Pop()
{
	return m_arrMemory[--m_nSP];
}

inline int CStack::operator[](int nOffset) const
{
	return m_arrMemory[nOffset];
}

inline int& CStack::operator[](int nOffset)
{
	return m_arrMemory[nOffset];
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////


#endif // STACK_H