#include "stdIncludes.h"
#include "acIncludes.h"
#include "vwScalerTypes.h"
#include "vwScaler.h"

//in ac channel is assumed only one pixel is driven and consumed at a time.
//no buffering is expected

#pragma hls_design top
void vwScaler(
  ac_channel<pxlT>   &pxlIAC,   //input pixels
  memT               &mem       //memory
) {

  //for size of input frame
  //  for size of input line
  //    getPxl(ac_channel<pxlInT> &pxlInAC, pxlInT &pxlIn)
  //    if(lineInIdx % 2 == 0) //replace with ac_int and check lsb for 0
  //      mem[lineInIdx>>1]  = getPxlAvg(pxlPrv, pxlIn);
  //    else
  //      pxlPrv  = pxlIn;

  static pxlCntIT   pxlCntI  = 0;
  static lineCntIT  lineCntI = 0;
         pxlCntOT   pxlCntO;
         lineCntOT  lineCntO;
  static pxlT       pxlPrvI;
         pxlT       pxlI, hPxlO, vPxlO;
  
  bool gotPxl  = getPxl(pxlIAC, pxlI);
  if(gotPxl) {
    //compute the output frame pointers
    pxlCntO   = pxlCntI >> 1;
    lineCntO  = lineCntI>> 1;
  
    if(isPxlCntOdd(pxlCntI)) {      //perform horizontal interpolation
      hPxlO  = getPxlAvg(pxlPrvI, pxlI);
      //cout<<"pxlPrvI:"<<pxlPrvI<<"  pxlI:"<<pxlI<<"  hPxlO:"<<hPxlO<<endl;

 
      if(isLineCntOdd(lineCntI)) {  //perform vertical interpolation
        vPxlO  = getPxlAvg(mem.frameO.lineBufAryO[lineCntO].pxlAryO[pxlCntO],
                           hPxlO);
        //cout<<"pxlPrvLn:"<<mem.frameO.lineBufAryO[lineCntO].pxlAryO[pxlCntO]
        //    <<"  hPxlO:"<<hPxlO<<"  vPxlO:"<<vPxlO<<endl;
      } else {
        vPxlO  = hPxlO;
      }
  
      //store pixel in output frame
      mem.frameO.lineBufAryO[lineCntO].pxlAryO[pxlCntO]  = vPxlO;
    }
 
    //store current pixel as previous, for next cycle
    pxlPrvI  = pxlI;
    //cout<<"  pxlI:"<<pxlI<<" pxlPrvI:"<<pxlPrvI<<endl;

/*
    //increment pixel and line pointers - will only work with native types
    if(++pxlCntI >= LineBufSzI) {      //end of line
      pxlCntI  = 0;
      cout<<"driving pxlCntI to 0"<<endl;
      if(++lineCntI >= FrameBufSzI) {  //end of frame
        cout<<"driving lineCntI to 0"<<endl;
        lineCntI  = 0;
      }
    }
*/
    //increment pixel and line pointers - for ac types, if width is just right,
    //then it will never reach size; example 3-bit, max val is 0x7 and size 8
    if(++pxlCntI >= LineBufSzI) {                     //end of line
      pxlCntI  = 0;
    }
    
    //dump the line buffer, once it is populated - for debugging
    //if(pxlCntI==0) {
    //  for(int i=0; i<LineBufSzO; i++) {
    //    cout<<mem.frameO.lineBufAryO[lineCntO].pxlAryO[i]<<" ";
    //  }
    //  cout<<endl;
    //}
    
    if((pxlCntI==0) && (++lineCntI >= FrameBufSzI)) {  //end of frame
      lineCntI  = 0;
    }
    //cout<<"pxlCntI:"<<pxlCntI<<"  lineCntI:"<<lineCntI<<endl;
  }
}

//-----------------------------------------------------------------------------
//read from ac channel
//-----------------------------------------------------------------------------
bool getPxl(ac_channel<pxlT> &pxlIAC, pxlT &pxlI) {
  bool gotPxl  = false;
  
#ifndef __SYNTHESIS__
  if(pxlIAC.available(1))
#endif
  {
    pxlI   = pxlIAC.read();
    //cout<<pxlI<<"  ";
    gotPxl = true;
  }
  
#ifndef __SYNTHESIS__
  if(pxlIAC.size() != 0) {
    cerr<<"spurious data waiting in pxlIAC channel"<<endl;
  }
#endif
  
  return gotPxl;
}


//-----------------------------------------------------------------------------
//obtain the average of two pixels
//-----------------------------------------------------------------------------
pxlT getPxlAvg(pxlT pxl1, pxlT pxl2) {
  //try it without the typecast
  //can multi-bit be accessed directly with getslc()
  pxlBgT  pxlSum  = (pxlBgT)pxl1 + (pxlBgT)pxl2;
  pxlT    pxlAvg  = pxlSum >> 1;  //divide by 2
  //cout<<pxl1<<" " <<pxl2<<" "<<pxlAvg<<endl;

  return pxlAvg;
}

//-----------------------------------------------------------------------------
//is the pixel counter value odd
//-----------------------------------------------------------------------------
bool isPxlCntOdd(pxlCntIT pxlCntI) {
  return pxlCntI[0];
}

//-----------------------------------------------------------------------------
//is the line counter value odd - may be squished as a template
//-----------------------------------------------------------------------------
bool isLineCntOdd(lineCntIT lineCntI) {
  return lineCntI[0];
}