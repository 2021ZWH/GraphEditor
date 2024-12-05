#include "GraphItemText.h"

GraphItemText::GraphItemText(PointF beginPos, PointF endPos, TCHAR* str, int strlen)
  :GraphItemRectangle::GraphItemRectangle(beginPos, endPos)
{
  m_VecText.resize(strlen);
  memcpy(str, m_VecText.data(), sizeof(TCHAR) * strlen);
}

GraphItemText::~GraphItemText()
{
  GraphItemRectangle::~GraphItemRectangle();
}

void GraphItemText::drawShape(HDC hdc)
{
  GraphItemRectangle::drawShape(hdc);

  XFORM OldForm;
  GetWorldTransform(hdc, &OldForm);
  ModifyWorldTransform(hdc, &m_xForm, MWT_RIGHTMULTIPLY);

}

bool GraphItemText::shapeResizeTo(const PointF& newPos, ControlHandler* handler)
{
  bool ret =GraphItemRectangle::shapeResizeTo(newPos, handler);

  return ret;


}
