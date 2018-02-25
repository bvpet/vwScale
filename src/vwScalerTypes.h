#ifndef __VWSCALER_TYPES_H__
#define __VWSCALER_TYPES_H__


//common pixel type
typedef ac_int<8,false>  pxlT;
typedef ac_int<pxlT::width+1, pxlT::sign> pxlBgT;


//-----------------------------------------------------------------------------
//Input frame
//-----------------------------------------------------------------------------
const int LineBufSzI  = 8;     //static assert, even no; Number of pixels

typedef struct{
  pxlT  pxlAry[LineBufSzI];
} lineBufIT;

const int FrameBufSzI = 12;    //static assert, even no; Number of lines
struct frameIT {
  lineBufIT lineBufAry[FrameBufSzI];
};

const int LineBufIdxWdI  = ac::log2_ceil<LineBufSzI>::val;
typedef ac_int<LineBufIdxWdI, false> pxlCntIT;

const int FrameBufIdxWdI  = ac::log2_ceil<FrameBufSzI>::val;
typedef ac_int<FrameBufIdxWdI, false> lineCntIT;


//-----------------------------------------------------------------------------
//Output frame
//-----------------------------------------------------------------------------
const int LineBufSzO  = LineBufSzI/2;  //no of pxl output
struct lineBufOT {
  pxlT  pxlAryO[LineBufSzO];
};

const int FrameBufSzO = FrameBufSzI/2;   //no of lines in frame output
struct frameOT {
  lineBufOT lineBufAryO[FrameBufSzO];
};


const int LineBufIdxWdO  = log2(LineBufSzO);
typedef ac_int<LineBufIdxWdO, false> pxlCntOT;

const int FrameBufIdxWdO  = log2(FrameBufSzO);
typedef ac_int<FrameBufIdxWdI, false> lineCntOT;


struct memT { 
  frameOT frameO;
};



#endif