#pragma once

#include "../Common/ConstantBufferMacros.h"
#include "../Common/Platforms.h"

CONSTANT_BUFFER2(ezSelectionHighlightConstants, 3, SET_RENDER_PASS)
{
  COLOR4F(HighlightColor);
  FLOAT1(OverlayOpacity);
};
