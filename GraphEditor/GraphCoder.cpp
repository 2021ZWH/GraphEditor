#include "GraphCoder.h"
#include "GraphItemLine.h"
#include "GraphItemPolyline.h"
#include "GraphItemPolyBezier.h"
#include "GraphItemCircle.h"
#include "GraphItemElliptic.h"
#include "GraphItemRectangle.h"

int GraphCoder::code(Vector<GraphItemShape*>& shapeVec, TCHAR** szData)
{
	Vector<TCHAR> textVec;
	for(int i = 0; i < shapeVec.size(); i++)
	{
		Vector<TCHAR> vec = shapeVec[i]->toText();

		if(i) textVec.push_back('\n');

		for(int i = 0; i < vec.size(); i++)
			textVec.push_back(vec[i]);
	}

	TCHAR* buffer = new TCHAR[textVec.size() + 1];
	if(buffer == nullptr)
		return -1;
	memcpy(buffer, textVec.data(), sizeof(TCHAR) * textVec.size());
	buffer[textVec.size()] = NULL;

	*szData = buffer;

	return 0;
}

int GraphCoder::decode(TCHAR* szData, Vector<GraphItemShape*>& shapeVec)
{
	int dataSize = lstrlen(szData);

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

	return 0;
}

int GraphCoder::parseLine(TCHAR* szData, int begin, GraphItemShape** shape)
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
		pItemShape->setProperty({ desData[1],desData[2] ,desData[3] ,(bool)desData[4] });
		*shape = pItemShape;
	}

	return end;
}

int GraphCoder::strToFloat(TCHAR* szData, int begin, double* val)
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

int GraphCoder::strToInt(TCHAR* szData, int begin, int* val)
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