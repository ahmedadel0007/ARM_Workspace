#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define NIBBLE    0b1111

// Set bit BIT in REG
#define SET_BIT(REG,BIT)    (REG |= (1<<BIT))
// Clear bit BIT in REG
#define CLR_BIT(REG,BIT)    (REG &= ~(1<<BIT))
// Toggle bit BIT in REG
#define TGL_BIT(REG,BIT)    (REG ^= (1<<BIT))
// Get bit BIT in REG
#define GET_BIT(REG,BIT)    ((REG>>BIT)&1)

// Set high nibble in REG
#define SET_HIGH_NIB(REG)   (REG |= (NIBBLE<<4))
// Clear high nibble in REG
#define CLR_HIGH_NIB(REG)   (REG &= ~(NIBBLE<<4))
// Get high nibble in REG
#define GET_HIGH_NIB(REG)   ((REG>>4)&NIBBLE)
// Toggle high nibble in REG
#define TGL_HIGH_NIB(REG)   (REG ^= (NIBBLE<<4))
// Set low nibble in REG
#define SET_LOW_NIB(REG)    (REG |= NIBBLE)
// Clear low nibble in REG
#define CLR_LOW_NIB(REG)    (REG &= ~NIBBLE)
// Get low nibble in REG
#define GET_LOW_NIB(REG)    (REG & NIBBLE)
// Toggle low nibble in REG
#define TGL_LOW_NIB(REG)    (REG ^= NIBBLE)

// Assign VALUE to REG
#define ASSIGN_REG(REG,VALUE)       (REG = VALUE)
// Assign VALUE to high nibble REG
#define ASSIGN_HIGH_NIB2(REG,VALUE) ( REG = (REG & ~(NIBBLE<<4) | (VALUE<<4)) )
#define ASSIGN_LOW_NIB2(REG,VALUE)   ( REG = (REG & ~(NIBBLE) | (VALUE)) )

#define ASSIGN_HIGH_NIB(REG,VALUE)  do{\
                                    CLR_HIGH_NIB(REG);\
                                    REG |= (VALUE<<4);\
                                    }while(0)

// Assign VALUE to low nibble REG
#define ASSIGN_LOW_NIB(REG,VALUE)  do{\
                                    CLR_LOW_NIB(REG);\
                                    REG |= VALUE;\
                                    }while(0)
// Right shift by NO in REG
#define RSHFT_REG(REG, NO)      (REG = REG>>NO)
// Left shift by NO in REG
#define LSHFT_REG(REG, NO)      (REG = REG<<NO)
// Circular right shift by NO in REG
#define CRSHFT_REG(REG, NO)     ( REG = (REG >> NO) | (REG << (8-NO)) )

// Circular left shift by NO in REG
#define CLSHFT_REG(REG,NO)      ( REG = (REG << NO) | (REG >> (8-NO)) )


#endif