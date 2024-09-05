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

int GraphFile::readFile(Vector<GraphItemShape*>& shapeVec)
{
	if(m_hFile == INVALID_HANDLE_VALUE) return -1;

	DWORD dwFileSize = GetFileSize(m_hFile, NULL);
	char* buffer = new char[dwFileSize];
	if(buffer == nullptr) return -1;

	DWORD dwReadSize;
	if(!ReadFile(m_hFile, buffer, dwFileSize, &dwReadSize, NULL))
	{
		delete[] buffer;
		return -1;
	}

	DWORD dataSize = MultiByteToWideChar(CP_UTF8, NULL, buffer, dwReadSize, NULL, NULL);
	TCHAR* szData = new TCHAR[dataSize];
	MultiByteToWideChar(CP_UTF8, NULL, buffer, dwReadSize, szData, dataSize);

	int now = 0;
	while(now < dataSize)
	{
		GraphItemShape* shape = nullptr;
		now = parseLine(szData, now, &shape) + 1;

		if(shape)
		{
			shapeVec.push_back(shape);
		}
	}

	return 1;
}

int GraphFile::writeFile(Vector<GraphItemShape*>& shapeVec)
{
	if(m_hFile == INVALID_HANDLE_VALUE) return -1;

	Vector<TCHAR> textVec;
	for(int i = 0; i < shapeVec.size(); i++)
	{
		Vector<TCHAR> vec = shapeVec[i]->toText();

		if(i) textVec.push_back('\n');

		for(int i = 0; i < vec.size(); i++)
			textVec.push_back(vec[i]);
	}

	TCHAR* outData = new TCHAR[textVec.size() + 1];
	if(outData == nullptr) return -1;
	memcpy(outData, textVec.data(), sizeof(TCHAR) * textVec.size());
	outData[textVec.size()] = NULL;

	DWORD bufferSize=WideCharToMultiByte(CP_UTF8, NULL, outData, textVec.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[bufferSize + 1];
	WideCharToMultiByte(CP_UTF8, NULL, outData, textVec.size(), buffer, bufferSize, NULL, NULL);
	DWORD dwWriteSize = 0;

	int ret = WriteFile(m_hFile, buffer, bufferSize, &dwWriteSize, NULL);
	
	delete[] outData;
	delete[] buffer;
	
	if(!ret)  return ret;
	return -1;
}

int GraphFile::strToFloat(TCHAR* szData, int begin, double* val)
{
	double res = 0;
	int pos = -1;
	int end = begin;
	int dataSize = lstrlen(szData);
	bool symbol = true;

	for(int i = begin; i < dataSize; i++)
	{
		if(szData[i] == '.')
		{
			pos = i;
		}
		else if(szData[i] <= '9' && szData[i] >= '0')
		{
			if(pos == -1)
			{
				res = res * 10 + (int)(szData[i] - '0');
			}
			else
			{
				res = res + (double)(szData[i] - '0') / pow(10, i - pos);
			}
		}
		else if(szData[i] == '-')
		{
			symbol = false;
		}
		else
		{
			end = i;
			break;
		}
	}

	*val = symbol ? res : -res;
	return end;
}

int GraphFile::strToInt(TCHAR* szData, int begin, int* val)
{
	int res = 0;
	int end = begin;
	int dataSize = lstrlen(szData);

	for(int i = begin; i < dataSize; i++)
	{
		if(szData[i] <= '9' && szData[i] >= '0')
		{
			res = res * 10 + (int)(szData[i] - '0');
		}
		else
		{
			end = i;
			break;
		}
	}
	*val = res;
	return end;
}

int GraphFile::parseLine(TCHAR* szData, int begin, GraphItemShape** shape)
{
	int end = begin;
	int dataSize = lstrlen(szData);

	while(end < dataSize)
	{
		if(szData[end] == '\n')
			break;
		end++;
	}

	unsigned int desData[6];
	memset(desData, 0, sizeof desData);
	Vector<PointF> aptf;
	int now = begin;
	for(int i = 0; i < 6; i++)
	{
		int val = 0;
		now = strToInt(szData, now, &val) + 1;
		desData[i] = val;
	}

	for(int i = 0; i < desData[5]; i++)
	{
		double x = 0, y = 0;
		now = strToFloat(szData, now, &x) + 1;
		now = strToFloat(szData, now, &y) + 1;
		aptf.push_back({ x,y });
	}

	GraphItemShape* pItemShape = nullptr;
	switch(desData[0])
	{
		case SHAPE_LINE:
			pItemShape = new GraphItemLine(aptf[0], aptf[1]);
			break;

		case SHAPE_POLYLINE:
		{
			pItemShape = new GraphItemPolyline(aptf[0]);
			for(int i = 1; i < aptf.size(); i++)
				pItemShape->addPos(aptf[i]);
			break;
		}

		case SHAPE_POLYBEZIER:
		{
			pItemShape = new GraphItemPolyBezier();
			for(int i = 0; i < aptf.size(); i++)
				pItemShape->addPos(aptf[i]);
			break;
		}

		case SHAPE_CIRCLE:
		{
			PointF beginPos = { min(aptf[0].x,aptf[2].x),min(aptf[0].y,aptf[2].y) };
			PointF endPos = { max(aptf[0].x,aptf[2].x),max(aptf[0].y,aptf[2].y) };
			pItemShape = new GraphItemCircle(beginPos, endPos);
			break;
		}

		case SHAPE_ELLIPTIC:
		{
			PointF beginPos = { min(aptf[0].x,aptf[2].x),min(aptf[0].y,aptf[2].y) };
			PointF endPos = { max(aptf[0].x,aptf[2].x),max(aptf[0].y,aptf[2].y) };
			pItemShape = new GraphItemElliptic(beginPos, endPos);
			break;
		}

		case SHAPE_RECTANGLE:
		{
			PointF beginPos = { min(aptf[0].x,aptf[2].x),min(aptf[0].y,aptf[2].y) };
			PointF endPos = { max(aptf[0].x,aptf[2].x),max(aptf[0].y,aptf[2].y) };
			pItemShape = new GraphItemRectangle(beginPos, endPos);
			break;
		}
	}

	if(pItemShape)
	{
		pItemShape->setLineWidth(desData[1]);
		pItemShape->setLineColor(desData[2]);
		pItemShape->setFillColor(desData[3]);
		pItemShape->setTransParent(desData[4]);
		*shape = pItemShape;
	}

	return end;
}