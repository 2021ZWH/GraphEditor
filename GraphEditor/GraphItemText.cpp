#include "GraphItemText.h"

GraphItemText::GraphItemText(PointF beginPos, PointF endPos, TCHAR* str, int strlen)
  :GraphItemRectangle::GraphItemRectangle(beginPos, endPos)
{
  m_VecText.resize(strlen);
  for(int i = 0; i < strlen; i++)
    m_VecText[i] = str[i];
}

GraphItemText::~GraphItemText()
{
  GraphItemShape::clearCtrHandler();
}

void GraphItemText::drawShape(HDC hdc)
{
  GraphItemRectangle::drawShape(hdc);

  XFORM OldForm;
  GetWorldTransform(hdc, &OldForm);
  ModifyWorldTransform(hdc, &m_xForm, MWT_RIGHTMULTIPLY);

  RectF rectf;
  rectf.left = min(m_aptF[0].x, m_aptF[2].x);
  rectf.right = max(m_aptF[0].x, m_aptF[2].x);
  rectf.top = min(m_aptF[0].y, m_aptF[2].y);
  rectf.bottom = max(m_aptF[0].y, m_aptF[2].y);

  RECT rect = rectf.toRect();
 
  DrawTextEx(hdc, m_VecText.data(), m_VecText.size(), &rect, DT_CENTER, NULL);

  SetWorldTransform(hdc, &OldForm);
}

bool GraphItemText::shapeResizeTo(const PointF& newPos, ControlHandler* handler)
{
  bool ret = GraphItemRectangle::shapeResizeTo(newPos, handler);

  return ret;


}
