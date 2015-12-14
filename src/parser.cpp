////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#include "parser.h"

// STD Includes
#include <map>
#include <fstream>
#include <iostream>
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

// Interface Methodes
std::shared_ptr<char> CParser::Parse(std::string const& strFilePath)
{
	std::ifstream inFile(strFilePath, std::ifstream::binary);
	std::filebuf* pFileBuf = inFile.rdbuf();

	int nSize = pFileBuf->pubseekoff(0, inFile.end, inFile.in);
	pFileBuf->pubseekpos(0, inFile.in);

	char* pBuffer = new (std::nothrow) char[nSize];
	pFileBuf->sgetn(pBuffer, nSize);

	inFile.close();
	std::cout.write(pBuffer, nSize);

	bool bFlag = false;
	COperations operations;
	std::string strInstruction = "";
	std::string strByteCode = "";
	std::map<std::string, int> mapLabelNameToOffset;
	std::map<std::string, int> mapJumpNameToOffset;
	for (int i = 0; i < nSize; ++i)
	{
		if ((pBuffer[i] != ' ' && pBuffer[i] != '\n'
			&& pBuffer[i] != '\t' && pBuffer[i] != '\r'
			&& pBuffer[i] != ';'))
		{
			strInstruction.push_back(pBuffer[i]);
		}
		else
		{
			if (strInstruction == "")
			{
				if (pBuffer[i] == ';')
				{
					while (pBuffer[i] != '\n')
						++i;
				}
			}
			else
			{
				if ((strInstruction[0] < '0') || (strInstruction[0] > '9'))
				{
					COperations::ECode eOpCode = operations.GetOpCode(strInstruction);
					int nOpCode = (int) (eOpCode);
					strInstruction = "";

					int nArgument = 0;
					std::string strArgument = "";
					for (++i; i < nSize; ++i)
					{
						if (pBuffer[i] == '\n' || pBuffer[i] == '\r')
						{
							if ((strArgument != "") && (strArgument[0] >= '0') && (strArgument[0] <= '9'))
								nArgument = std::stoi(strArgument);

							break;
						}

						strArgument.push_back(pBuffer[i]);
					}

					if (eOpCode == COperations::ECode::LABEL)
					{
						mapLabelNameToOffset.emplace(strArgument, strByteCode.size());

						continue;
					}

					strByteCode += (char) (nOpCode);

					if ((eOpCode == COperations::ECode::JUMP) || (eOpCode == COperations::ECode::JZ) ||
						(eOpCode == COperations::ECode::JNZ))
					{
						auto mapIterator = mapLabelNameToOffset.find(strArgument);
						if (mapIterator == mapLabelNameToOffset.end())
						{
							mapJumpNameToOffset.emplace(strArgument, strByteCode.size());
							strByteCode += "    ";
						}
						else
						{
							nArgument = mapIterator->second;

							char* pTemChar;
							pTemChar = (char*) &nArgument;

							for (int i = 0; i < 4; ++i)
								strByteCode += pTemChar[i];
						}

						continue;
					}

					if (eOpCode == COperations::ECode::PUSHC)
					{
						char* pTemChar;
						pTemChar = (char*) &nArgument;

						for (int i = 0; i < 4; ++i)
							strByteCode += pTemChar[i];
					}

					if ((eOpCode == COperations::ECode::PUSHR) || (eOpCode == COperations::ECode::PUSHA) ||
						(eOpCode == COperations::ECode::POPR) || (eOpCode == COperations::ECode::POPA))
					{
						strByteCode += strArgument[0] + strArgument[1];

						if ((eOpCode == COperations::ECode::PUSHA) || (eOpCode == COperations::ECode::POPA))
						{
							strArgument.erase(0, 2);

							if (strArgument != "")
								nArgument = std::stoi(strArgument);

							char* pTemChar;
							pTemChar = (char*) &nArgument;

							for (int i = 0; i < 4; ++i)
								strByteCode += pTemChar[i];
						}

						continue;
					}

				}
				else // interrupt
				{
					strInstruction = "";
				}
			}
		}
	}
	delete[] pBuffer;

	int nOpCode = (int) (COperations::ECode::HALT);
	strByteCode += (char) (nOpCode);

	for (auto mapIterator = mapJumpNameToOffset.begin(); mapIterator != mapJumpNameToOffset.end(); ++mapIterator)
	{
		std::string strLabelName = mapIterator->first;
		int nOffset = mapLabelNameToOffset.at(strLabelName);
		int nPosition = mapIterator->second;

		char* pTemChar;
		pTemChar = (char*) &nOffset;

		for (int i = 0; i < 4; ++i)
			strByteCode[nPosition + i] = pTemChar[i];
	}

	std::shared_ptr<char> pChar(new char[strByteCode.size()]);
	for (int i = 0; i < strByteCode.size(); ++i)
	{
		pChar.get()[i] = strByteCode[i];
	}

	return pChar;
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace parser
////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////