// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <pspkernel.h>
#include <psppower.h>
#include <pspsdk.h>
#include <pspusb.h>
#include <pspusbstor.h>
#include <stdio.h>
#include <stdarg.h>

#include "common.h"
#include "level.h"
#include "disp.h"
#include "game.h"
#include "language.h"
#include "lua.h"
#include "audio.h"
#include "config.h"

/* Callbacks */
int exit_callback(int arg1, int arg2, void *common) {
  sceKernelExitGame();
  return 0; }
int CallbackThread(SceSize args, void *argp) {
  int cbid;
  cbid = sceKernelCreateCallback("Exit Callback",exit_callback,NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();
  return 0; }
int SetupCallbacks() {
  int thid = 0;
  thid = sceKernelCreateThread("update_thread",CallbackThread,0x11,0xFA0,0,0);
  if(thid >= 0) sceKernelStartThread(thid, 0, 0);
  return thid; }

PSP_MODULE_INFO("App", 0, 1, 1);
PSP_HEAP_SIZE_KB(-4096);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int thread_block = 0, thread_disp_waiting = 0;
int exit_state = 0;
char exit_err[ERROR_LEN] = "";
char cwd[512];

void throwException(const char* err, ...)
{
  char buf[ERROR_LEN];
  va_list ap;  
  va_start(ap,err);
  vsnprintf(buf,ERROR_LEN,err,ap);
  va_end(ap);
  buf[ERROR_LEN-1] = '\0';
  strncat(exit_err,buf,ERROR_LEN);
  exit_state = EXCEPTION;
}


void usbStorage()
{
  pspSdkLoadStartModule("flash0:/kd/chkreg.prx",PSP_MEMORY_PARTITION_KERNEL);
  pspSdkLoadStartModule("flash0:/kd/npdrm.prx",PSP_MEMORY_PARTITION_KERNEL);
  pspSdkLoadStartModule("flash0:/kd/semawm.prx",PSP_MEMORY_PARTITION_KERNEL);
  pspSdkLoadStartModule("flash0:/kd/usbstor.prx",PSP_MEMORY_PARTITION_KERNEL);
  pspSdkLoadStartModule("flash0:/kd/usbstormgr.prx",PSP_MEMORY_PARTITION_KERNEL);
  pspSdkLoadStartModule("flash0:/kd/usbstorms.prx",PSP_MEMORY_PARTITION_KERNEL);
  pspSdkLoadStartModule("flash0:/kd/usbstorboot.prx",PSP_MEMORY_PARTITION_KERNEL);
  pspSdkLoadStartModule("flash0:/kd/usbdevice.prx",PSP_MEMORY_PARTITION_KERNEL);
  sceUsbStart(PSP_USBBUS_DRIVERNAME,0,0);
  sceUsbStart(PSP_USBSTOR_DRIVERNAME,0,0);
  sceUsbstorBootSetCapacity(0x800000);
  sceUsbActivate(0x1c8);
}


int main(int argc, char* argv[])
{
  SetupCallbacks();
  #ifdef DEBUG
    usbStorage();
  #endif

  strcpy(cwd,argv[0]);
  cwd[strlen(cwd)-strlen("/eboot.pbp")] = '\0';

  configLoad();
  initLanguage();
  initAudio();
  initLua();
  initGame();
  initDisp();

  sceKernelSleepThread();
  return 0;
}

// EOF
