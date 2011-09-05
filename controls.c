// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <pspctrl.h>

SceCtrlData pad, oldPad;

int buttonPressed(unsigned int btn)
{
  return (((pad.Buttons & btn) == btn) ? 1 : 0);
}


int buttonWasPressed(unsigned int btn)
{
  return (((oldPad.Buttons & btn) == btn) ? 1 : 0);
}


int buttonJustPressed(unsigned int btn)
{
  return buttonPressed(btn) && (!buttonWasPressed(btn));
}


int buttonJustReleased(unsigned int btn)
{
  return !buttonPressed(btn) && buttonWasPressed(btn);
}


void updateControls()
{
  oldPad = pad;
  sceCtrlPeekBufferPositive(&pad,1);
}


SceCtrlData* getPad()
{
  return &pad;
}


SceCtrlData* getOldPad()
{
  return &oldPad;
}
