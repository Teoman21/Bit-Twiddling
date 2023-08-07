#include "floatx.h"
#include "bitFields.h"
#include <assert.h>
#include <limits.h> // for CHAR_BIT - number of bits per byte
#include <math.h> // for isinf and isnan

floatx doubleToFloatx(double val, int totBits, int expBits) {
    assert(totBits >= 2 && totBits <= 64);
    assert(expBits >= 1 && expBits < totBits - 1);

    union hexDouble {
        double dbl;
        long lng;
    } unionVal;

    unionVal.dbl = val;

    int fracBits = totBits - expBits - 1;
    int expBias = (1 << (expBits - 1)) - 1;
    int doubleExpBias = 1023;

    
    int signBit = getBit(63, unionVal.lng);

    if (val == 0.0) {
        return 0;
    } else if (isinf(val)) {
        return ((unsigned long)signBit << (totBits - 1)) | ((1UL << expBits) - 1UL) << (fracBits);
    } else if (isnan(val)) {
        return ((unsigned long)signBit << (totBits - 1)) | ((1UL << expBits) - 1UL) << (fracBits) | 1UL;
    }

    // Extract biased exponent and fraction
    int biasedExponent = getBitFldU(62, 11, unionVal.lng);
    unsigned long fraction = getBitFldU(51, 52, unionVal.lng);

   
    if (biasedExponent == 0) {
        // Handle sub-normal case in double
        int leadingZeros = __builtin_clzl(fraction) - (64 - 52);
        biasedExponent = 1 - doubleExpBias - leadingZeros;
        fraction <<= (leadingZeros + 1);
    } else {
        fraction &= ((1UL << 52) - 1);
    }

    // Calculate floatx biased exponent
    int floatxBiasedExponent = biasedExponent - doubleExpBias + expBias;

    // Check if floatx value should be subnormal or overflow
    if (floatxBiasedExponent <= 0) {
        // Shift fraction right to handle subnormal numbers in floatx
        int shift = 1 - floatxBiasedExponent;
        fraction >>= shift;
        floatxBiasedExponent = 0;
    } else if (floatxBiasedExponent >= ((1 << expBits) - 1)) {
        // Handle overflow case
        floatxBiasedExponent = (1 << expBits) - 1;
        fraction = 0;
    }

    // Truncate or extend fraction
    if (fracBits < 52) {
        fraction >>= (52 - fracBits);
    } else if (fracBits > 52) {
        fraction <<= (fracBits - 52);
    }

    unsigned long floatxVal = ((unsigned long)signBit << (totBits - 1)) | ((unsigned long)floatxBiasedExponent << fracBits) | fraction;

    return floatxVal;
}