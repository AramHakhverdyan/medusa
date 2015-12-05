#ifndef MEDUSA_H
#define MEDUSA_H

////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#ifndef PROCESS_H
#	include "process.h"
#endif

#ifndef MODULE_H
#	include "module.h"
#endif

// STD Includes
#include <string>
#include <memory>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// class CMedusa
//
class CMedusa
{
public:// Constructors
	inline CMedusa();
	CMedusa(std::string const& strFilePath);
	~CMedusa()
	{}

public:// Interface Methodes
	inline void Execute();
	inline int CreateProcess(std::string const& strFilePath);

protected:// Helper Functions
	int CreateProcess(std::shared_ptr<CModule> pModule);

	inline void StartProcess(int const nProcessID);
	void StartAllProcess();

	inline int GenerateProcessID() const;

private:// Members
	std::map< int, std::shared_ptr<CProcess> > m_mapIDToProcess;
	std::shared_ptr<CModuleManager> m_pModuleManager;
};
////////////////////////////////////////////////////////////////////////////////

///////////////////////// Implementing inline methods //////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CMedusa
//

// Constructors
inline CMedusa::CMedusa()
	: m_pModuleManager(new (std::nothrow) CModuleManager),
	  m_mapIDToProcess()
{
}

// Interface Methodes
inline void CMedusa::Execute()
{
	StartAllProcess();
}

inline int CMedusa::CreateProcess(std::string const& strFilePath)
{
	std::shared_ptr<CModule> pModule = m_pModuleManager->Load(strFilePath);

	return CreateProcess(pModule);
}

// Helper Functions
inline void CMedusa::StartProcess(int const nProcessID)
{
	std::shared_ptr<CProcess> pProcess = m_mapIDToProcess.at(nProcessID);
	pProcess->Start();
}

inline int CMedusa::GenerateProcessID() const
{
	static int ID = 0;
	return ID++;
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////


#endif // MEDUSA_H