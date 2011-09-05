// gLibVFPU by Geecko.
//
// This work is licensed under the Creative Commons BY-SA 3.0 Unported License.
// See LICENSE for more details.
//
// Please report bugs at : geecko.dev@free.fr

float gvfpu_sin(float a)
{
  float r;
  __asm__ volatile (
    "mtv   %1, s000\n"          // s000 = a
    "vcst.s s001, VFPU_2_PI\n"  // s001 = 2/pi
    "vmul.s s000, s000, s001\n" // s000 = s000*s001 (vsin ∈ [-1;1])
    "vsin.s s000, s000\n"       // s000 = sinf(s000)
    "mfv   %0, s000\n"          // r = s000
    : "=r"(r) : "r"(a)
  );
  return r;
}


float gvfpu_cos(float a)
{
  float r;
  __asm__ volatile (
    "mtv   %1, s000\n"          // s000 = a
    "vcst.s s001, VFPU_2_PI\n"  // s001 = 2/pi
    "vmul.s s000, s000, s001\n" // s000 = s000*s001 (vcos ∈ [-1;1])
    "vcos.s s000, s000\n"       // s000 = cosf(s000)
    "mfv   %0, s000\n"          // r = s000
    : "=r"(r) : "r"(a)
  );
  return r;
}


float gvfpu_sqrt(float a)
{
  float r;
  __asm__ volatile (
    "mtv    %1, s000\n"    // s000 = a
    "vsqrt.s s000, s000\n" // s000 = sqrtf(s000)
    "mfv    %0, s000\n"    // r = s000
    : "=r"(r) : "r"(a)
  );
  return r;
}


float gvfpu_hypot(float a, float b)
{
  float r;
  __asm__ volatile (
    "mtv    %1, s000\n"          // s000 = a
    "mtv    %2, s001\n"          // s001 = b
    "vdot.p  s002, c000, c000\n" // s002 = s000*s000 + s001*s001
    "vsqrt.s s002, s002\n"       // s002 = sqrtf(s002)
    "mfv    %0, s002\n"          // r = s002
    : "=r"(r) : "r"(a), "r"(b)
  );
  return r;
}


float gvfpu_abs(float a)
{
  float r;
  __asm__ volatile (
    "mtv    %1, s000\n"   // s000 = a
    "vabs.s s000, s000\n" // s000 = fabsf(s000)
    "mfv    %0, s000\n"   // r = s000
    : "=r"(r) : "r"(a)
  );
  return r;
}


int gvfpu_floor(float a)
{
  int r;
  __asm__ volatile (
    "mtv     %1, s000\n"      // s000 = a
    "vf2id.s s000, s000, 0\n" // s000 = (int)floorf(s000)
    "mfv     %0, s000\n"      // r = s000
    : "=r"(r) : "r"(a)
  );
  return r;
}


int gvfpu_ceil(float a)
{
  int r;
  __asm__ volatile (
    "mtv     %1, s000\n"      // s000 = a
    "vf2iu.s s000, s000, 1\n" // s000 = (int)ceilf(s000)
    "mfv     %0, s000\n"      // r = s000
    : "=r"(r) : "r"(a)
  );
  return r;
}
