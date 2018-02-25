#ifndef __VWSCALER_H__
#define __VWSCALER_H__

//function prototype
void vwScaler(
  ac_channel<pxlT>  &pxlIAC,   //input pixels
  memT              &mem       //memory
);

//-----------------------------------------------------------------------------
//read from ac channel
//-----------------------------------------------------------------------------
bool getPxl(ac_channel<pxlT> &pxlIAC, pxlT &pxlI);

//-----------------------------------------------------------------------------
//obtain the average of two pixels
//-----------------------------------------------------------------------------
pxlT getPxlAvg(pxlT pxl1, pxlT pxl2);


//-----------------------------------------------------------------------------
//is horizontal or vertical count odd number
//-----------------------------------------------------------------------------
bool isPxlCntOdd(pxlCntIT pxlCntI);
bool isLineCntOdd(lineCntIT lineCntI);


#endif
