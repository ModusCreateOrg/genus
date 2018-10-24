#include <stdio.h>
#include <stdint.h>
#include <math.h>

bool compare(int8_t buf1[], int8_t buf2[], int len) {
  for (int i=0; i<len; i++) {
    if (buf1[i] != buf2[i]) {
      return false;
    }
  }
  return true;
}

void xcomp() {
  int64_t mFrame = 1;
  int8_t buf1[320], buf2[320], bigbuf[320*1000];

  int ndx = 0;
  for (int x=0; x<320; x++) {
    buf1[x] = sin(mFrame * 0.11 + x * 0.12) * 3.0f;
    bigbuf[ndx++] = buf1[x];
  }
  while (mFrame < 1000) {
    mFrame++;
    for (int x=0; x<320; x++) {
      buf2[x] = sin(mFrame * 0.11 + x * 0.12) * 3.0f;
      bigbuf[ndx++] = buf2[x];
    }

    // try to see if current 320 bytes exists in bigbuf
    for (int x = 0; x<ndx-320; x++) {
      if (compare(&bigbuf[x], buf2, 320)) {
        printf("mFrame: %lld, x: %d\n", mFrame, x);
        break;
      }
    }
    // try to see if current 320 bytes matches the 1st
    bool flag = true;
    for (int x=0; x<320; x++) {
      if (buf2[x] != buf1[x]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      printf("%lld\n", mFrame);
      break;
    }
  }

//  for (int x=0; x<320; x++) {
//    printf("%3d: %d\n", x, buf1[x]);
//  }
  
}

void ycomp() {
  int64_t mFrame = 1;
  int8_t buf1[240], buf2[240], bigbuf[240*1000];

  int ndx = 0;
  for (int x=0; x<240; x++) {
    buf1[x] = sin(mFrame * 0.1 + x * 0.05) * 2.0f;
    bigbuf[ndx++] = buf1[x];
  }
  while (mFrame < 1000) {
    mFrame++;
    for (int x=0; x<240; x++) {
      buf2[x] = sin(mFrame * 0.1 + x * 0.05) * 2.0f;
      bigbuf[ndx++] = buf2[x];
    }

    // try to see if current 320 bytes exists in bigbuf
    for (int x = 0; x<ndx-240; x++) {
      if (compare(&bigbuf[x], buf2, 240)) {
        printf("mFrame: %lld, x: %d\n", mFrame, x);
        break;
      }
    }
    // try to see if current 320 bytes matches the 1st
    bool flag = true;
    for (int x=0; x<240; x++) {
      if (buf2[x] != buf1[x]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      printf("%lld\n", mFrame);
      break;
    }
  }

//  for (int x=0; x<320; x++) {
//    printf("%3d: %d\n", x, buf1[x]);
//  }
}
int main() {
  xcomp();
  ycomp();
  return 0;
}

#if 0
// use this (or close to it) in playfield constructor
void precalc() {
  const int xmax = 460;
  const int ymax = 480;

  mXComp = (TInt8 *)AllocMem(320*xmax, MEMF_SLOW);
  mYComp = (TInt8 *)AllocMem(240*ymax, MEMF_SLOW);

  TInt8 *ptr;

  for (TInt64 mFrame = 0, ptr = mXComp; mFrame < 460; mFrame++) {
    for (int x =0; x<320; x++) {
      *ptr++ = sin(mFrame * 0.11 + x * 0.12) * 3.0f;
    }
  }
  for (TInt64 mFrame = 0, ptr = mYComp; mFrame < 380; mFrame++) {
    for (int y=0; y<240; y++) {
      *ptr++ = sin(mFrame * 0.1 + y * 0.05) * 2.0f;
    }
  }
}
#endif
