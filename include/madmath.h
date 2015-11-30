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
