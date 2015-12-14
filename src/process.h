#ifndef PROCESS_H
#define PROCESS_H

////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#ifndef STACK_H
#	include "stack.h"
#endif

#ifndef CONTEXT_H
#	include "context.h"
#endif

#ifndef EXPRESSION_H
#	include "expression.h"
#endif

#ifndef MODULE_H
#	include "module.h"
#endif

// STD Includes
#include <map>
#include <memory>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// class CProcess
//
class CProcess
{
public:// Constructors
	inline CProcess(std::shared_ptr<CModule> pModule);
	inline ~CProcess() = default;

public:// Interface Methodes
	void Start();
	void End();

	inline std::shared_ptr<const CStack> GetStack() const;
	inline std::shared_ptr<const CModule> GetModule() const;
	inline std::shared_ptr<const CContext> GetContext() const;

private:
	std::shared_ptr<CStack> m_pStack;
	std::shared_ptr<CModule> m_pModule;
	std::shared_ptr<CContext> m_pContext;
	std::unique_ptr<expr::CExpressionManager> m_pExpressionManager;
};
////////////////////////////////////////////////////////////////////////////////

///////////////////////// Implementing inline methods //////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CProcess
//

// Constructors
CProcess::CProcess(std::shared_ptr<CModule> pModule)
	: m_pModule(pModule),
	  m_pExpressionManager(new expr::CExpressionManager(pModule))
{
	m_pStack = std::shared_ptr<CStack>(new CStack(100));
	m_pContext = std::shared_ptr<CContext>(new CContext(m_pStack, m_pModule));
}

// Interface Methodes
inline std::shared_ptr<const CStack> CProcess::GetStack() const
{
	return m_pStack;
}

inline std::shared_ptr<const CModule> CProcess::GetModule() const
{
	return m_pModule;
}

inline std::shared_ptr<const CContext> CProcess::GetContext() const
{
	return m_pContext;
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////


#endif // PROCESS_H