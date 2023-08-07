#include "bitFields.h"
#include <assert.h>

int getBit(int bn,unsigned long val) {

  assert(bn>=0 && bn<=63);

  if((val >>bn) &1){
    // right shift and if the bit is 1 or not;
    return 1;
  }
  
  else{

    return 0;
  }
  
	// TODO:
	//		check to make sure bn is a valid bit position in long (you may assert this is true)
	//		If the bit in val at position bn is 1, return 1
	//		otherwise return 0.

// replace this with the correct code
}

void setBit(int bn,int new,unsigned long *val) {
  
  assert(bn>=0 && bn<=63);

 if (new) {
        *val |= 1ul << bn;
    } else

   {
        *val &= ~(1ul << bn);
    }
  // TODO:
	//		check to make sure bn is a valid bit position in long (you may assert this is true)
	//		if new is true, set the bit in val at bn to 1
	//     otherwise, set the bit in val at bn to 0
}

long getBitFld(int bs,int len,unsigned long val) {

  assert(bs>=0 && bs<=63);
  assert(len >=1 && bs - len +1 >=0);


  unsigned long unsigned_result = getBitFldU(bs, len, val);

  unsigned long sign_bit = (unsigned_result >> (len - 1));

    
    if (sign_bit != 0) {
      unsigned_result |= (~(0UL)<<len);
        
    }

    
    return (long) unsigned_result;
  //A mask defines which bits you want to keep, and which bits you want to clear.
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)
	// 		perform an unsigned getBitFldU to extract the unsigned version of the field
	//		get the high order bit of the result... that's the "sign" bit
	//		if the sign bit not zero, replace the 0 padding with 1 padding
	 // replace this with the correct code
}

unsigned long getBitFldU(int bs,int len,unsigned long val) {

  assert(bs >=0 && bs<= 63);
  assert(len>=1 && bs - len +1 <= 64);
  
  unsigned long mask = (1UL << len)-1;

  mask <<= (bs -len +1);

  unsigned long bitfld = val & mask;

  bitfld >>= (bs - len +1);

  return bitfld;
  
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)
	// 		make a mask that has len 1's
	// 		Shift that mask left so it's leftmost 1 starts at bs
	//      bitwise and the mask and val to isolate the bit field bits
	//		Shift the result to the right so that the rightmost bit of the bit field is bit 0
	//			Note that shift right pads to the left with the sign bit if the field is signed, but
	//			for unsigned, it will pad to the left with 0
 // replace this with the correct code
}

void setBitFld(int bs,int len,unsigned long new,unsigned long *val) {

  assert(bs >= 0 && bs < 64 && len > 0 && len <= 64 && bs - len +1 <= 64);

    // Create a mask with len bits, right justified
    unsigned long mask = (1UL << len) - 1UL;

    mask <<= (bs-len+1);
    new <<= (bs-len+1);
    new &= mask;
    *val &= ~mask;

    *val |= new;
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)
	//      Make a mask that has len bits, right justified
	//		Use mask to turn off any bits to the left of the bitField values in new
	// 		Shift both the new value and the mask to the correct bit position
	//		Turn off all bits in *val under the mask by bitwise anding with ~mask
	//		Or *val with new.  (new has zeros for all non bit field positions, so won't affect val)
}