#include "stdIncludes.h"
#include "acIncludes.h"
#include "vwScalerTypes.h"
#include "vwScaler.h"
#include "vwScalerTB.h"


int main(int argc, char* argv[]) {
  ac_channel<pxlT>  pxlIAC;
  memT              mem;
  
  //input pixel array - populate with known values for now
  frameIT frameI;               //use vector here
  bool    endOfFrame{false};
  bool    pushdPxl{false};
  int     hCnt{0}, vCnt{0};
  
  //initialize the input frame - some dummy image
  for(int vCnt=0; vCnt<FrameBufSzI; vCnt++) {
    for(int hCnt=0; hCnt<LineBufSzI; hCnt++) {
      frameI.lineBufAry[vCnt].pxlAry[hCnt]  = (vCnt + hCnt);
    }                          
  }
  
  printFrameI(frameI);
 
  while(!endOfFrame) {
    vwScaler(pxlIAC, mem);

    pushdPxl = putPxl(pxlIAC, frameI.lineBufAry[vCnt].pxlAry[hCnt]);
    if(pushdPxl) {  
      //increment frame pointers
      if(++hCnt >= LineBufSzI) {        //end of line
        hCnt  = 0;
        if(++vCnt >= FrameBufSzI) { //end of frame
          vCnt = 0;
          endOfFrame = true;
        }
      }
    }
    //cout<<"hCnt:"<<hCnt<<" vCnt:"<<vCnt<<endl;
  }
  
  //since vwScaler would not have completed scaling
  for(int i=0; i<10; i++) {
    vwScaler(pxlIAC, mem);
  }
  
  //output the frame for analysis
  printFrameO(mem.frameO);   
  
  cout<<"end of tb\n";  
}                        


//-----------------------------------------------------------------------------
//print frame routines
//-----------------------------------------------------------------------------
void printFrameI(frameIT frameI) {
  cout<<"Frame input\n";
  for(int v=0; v<FrameBufSzI; v++) {
    for(int h=0; h<LineBufSzI; h++) {
      cout<<setw(4)<<frameI.lineBufAry[v].pxlAry[h];
    }
    cout<<"\n";
  }  
}

void printFrameO(frameOT frameO) {
  cout<<"Frame output\n";
  for(int v=0; v<FrameBufSzO; v++) {
    for(int h=0; h<LineBufSzO; h++) {
      cout<<setw(4)<<frameO.lineBufAryO[v].pxlAryO[h];
    }                       
    cout<<"\n";              
  }                                 
}              
                  

//-----------------------------------------------------------------------------
//put pixel
//-----------------------------------------------------------------------------
bool putPxl(ac_channel<pxlT> &pxlIAC, pxlT pxlI) {
  pxlIAC.write(pxlI);
  
#ifndef __SYNTHESIS__ 
  int pxlIACSz  = pxlIAC.size();     
  if(pxlIACSz > 1) {
    cerr<<"Unconsumed pixel in input AC channel, size"<<pxlIACSz<<"\n";
  }              
#endif
  
  return true;  
}

