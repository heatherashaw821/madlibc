////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////


#ifndef MADMATH_H
#define MADMATH_H

#define RSR(v, s) \
    lambda(typeof(v), (typeof(v) value, typeof(s) bits){ \
        const unsigned int mask = (CHAR_BIT*sizeof(value)-1); \
        bits &= mask; \
        return (value>>bits) | (value<<( (-bits) & mask )); \
    })(v, s)

#define RSL(v, s) \
    lambda(typeof(v), (typeof(v) value, typeof(s) bits){ \
        const unsigned int mask = (CHAR_BIT*sizeof(value)-1); \
        bits &= mask; \
        return (value<<bits) | (bits>>( (-bits) & mask ));\
    })(v, s)


#endif
