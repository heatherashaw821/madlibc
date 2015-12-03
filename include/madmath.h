////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////


#ifndef MADMATH_H
#define MADMATH_H

#define RSR(v, s) (typeof(v)) (v >> (s & (CHAR_BIT*sizeof(v)-1)) | ((s & (CHAR_BIT*sizeof(v)-1)) << ( (-(s & (CHAR_BIT*sizeof(v)-1))) & (CHAR_BIT*sizeof(v)-1) )))
#define RSL(v, s) (typeof(v)) (v << (s & (CHAR_BIT*sizeof(v)-1)) | ((s & (CHAR_BIT*sizeof(v)-1)) >> ( (-(s & (CHAR_BIT*sizeof(v)-1))) & (CHAR_BIT*sizeof(v)-1) )))


#endif
