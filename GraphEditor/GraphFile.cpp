#include "GraphFile.h"
#include "GraphItemLine.h"
#include "GraphItemPolyline.h"
#include "GraphItemPolyBezier.h"
#include "GraphItemCircle.h"
#include "GraphItemElliptic.h"
#include "GraphItemRectangle.h"

GraphFile::GraphFile(const TCHAR* szFilename, FileMode mode)
{
	m_fileMode = mode;
	m_hFile = CreateFile(szFilename,
		mode == READ ? GENERIC_READ : GENERIC_WRITE,
		0,
		NULL,
		mode == READ ? OPEN_EXISTING : CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		0);
}

GraphFile::~GraphFile()
{
	if(m_hFile != INVALID_HANDLE_VALUE)
		CloseHandle(m_hFile);
}

bool GraphFile::isOpen() const
{
	return m_hFile != INVALID_HANDLE_VALUE;
}

int GraphFile::readFile(TCHAR** szData)
{
	if(m_hFile == INVALID_HANDLE_VALUE) 
		return -1;

	DWORD dwFileSize = GetFileSize(m_hFile, NULL);
	char* buffer = new char[dwFileSize];
	if(buffer == nullptr) 
		return -1;

	DWORD dwReadSize;
	if(!ReadFile(m_hFile, buffer, dwFileSize, &dwReadSize, NULL))
	{
		delete[] buffer;
		return -1;
	}

	DWORD dataSize = MultiByteToWideChar(CP_UTF8, NULL, buffer, dwReadSize, NULL, NULL);
	TCHAR* szOut = new TCHAR[dataSize];
	MultiByteToWideChar(CP_UTF8, NULL, buffer, dwReadSize, szOut, dataSize);

	*szData = szOut;
	return 0;
}

int GraphFile::writeFile(TCHAR* szData)
{
	if(m_hFile == INVALID_HANDLE_VALUE) 
		return -1;
	int dataSize = lstrlen(szData);

	DWORD bufferSize=WideCharToMultiByte(CP_UTF8, NULL, szData, dataSize, NULL, 0, NULL, NULL);
	char* buffer = new char[bufferSize + 1];
	WideCharToMultiByte(CP_UTF8, NULL, szData, dataSize, buffer, bufferSize, NULL, NULL);
	DWORD dwWriteSize = 0;

	int ret = WriteFile(m_hFile, buffer, bufferSize, &dwWriteSize, NULL);

	delete[] buffer;
	
	if(ret == FALSE)
		return -1;
	return 0;
}
