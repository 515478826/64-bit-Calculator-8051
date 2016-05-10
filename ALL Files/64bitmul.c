
/* Copyright (c) Microsoft Corporation. All rights reserved. */

/* Portable 64-bit integer math functions for MMLite
 */
#define __NO_BUILTIN_INT64 1
#if defined(MMLITE)
#include <mmlite.h>
#include <machdep.h>
#include "std_types.h"
#else
#define INT64 MYINT64
#define UINT64 MYUINT64
#include <windows.h>
#undef INT64
#undef UINT64
typedef struct _INT64 INT64;
typedef struct _UINT64 UINT64;
#define EXTERN_C extern
#include "int64.h"
#endif

/* Cannot (and should not) compile this if there is compiler support.
 * Dont think you can have it both ways because of alignment issues.
 * Someday the unions might get smarter.
 */
/* Well then, we'll give it another shot.  If there is compiler support
 * we'll just make sure the compiler support routines work.  So the code
 * in there is only used by the test programs e.g. tstdiv64.c & friends.
 */

/* Nullify macros for functions we define. If we get compiled then
 * it means that those macros are needed as functions.
 */
#undef Int64TimesInt64
#undef Int64TimesInt32
#undef Uint64TimesUint64
#undef Uint64TimesUint32

#ifndef Uint32TimesUint32
#define Uint32TimesUint32(_a_,_b_) ((_a_) * (_b_))
#endif


#if !defined(__TCS__)
#define MUX(a,b,c)     ((a) ? (b) : (c))
#define iabs(a) ((INT32)(a) < 0 ? -(INT32)(a) : (a))
/* umulm returns the high 32 bits of 32x32->64 multiplication */
unsigned long  umulm(UINT32 a, UINT32 b);
#endif

#if defined(_MSC_VER)
#pragma warning(disable:4146)  /* unary minus to unsigned type, result still unsigned */
#endif

/* MMLite runtime library function -- Multiply a signed,
 * 64-bit integer by a signed, 64-bit integer.  The
 * return value (the product) is a signed 64-bit integer.
 */
INT64 Int64TimesInt64(INT64 x, INT64 y)
{
    UINT32 x0, x1, y0, y1, z0, z1;
    INT64 z;
    int sign, xneg, yneg;

    /* Remember sign of result.
     */
    sign = (x.HighPart ^ y.HighPart) >> 31;

    /* Take absolute values of multiplicand x and multiplier y.
     */
    xneg = (x.HighPart < 0);
    x1 = MUX(xneg, ~x.HighPart + !x.LowPart, x.HighPart);
    x0 = MUX(xneg, -x.LowPart, x.LowPart);
    yneg = (y.HighPart < 0);
    y1 = MUX(yneg, ~y.HighPart + !y.LowPart, y.HighPart);
    y0 = MUX(yneg, -y.LowPart, y.LowPart);

    /* Perform the unsigned 32-by-32 multiplications.
     */
    z0 = Uint32TimesUint32(x0,y0);
    z1 = Uint32TimesUint32(x0,y1) + Uint32TimesUint32(x1,y0) + umulm(x0, y0);

    /* If necessary, negate product.
     */
    z.HighPart = MUX(sign, ~z1 + !z0, z1);
    z.LowPart = MUX(sign, -z0, z0);
    return (z);
}


/* MMLite runtime library function -- Multiply a signed,
 * 64-bit integer by a signed, 32-bit integer.  The
 * return value (the product) is a signed 64-bit integer.
 */
INT64 Int64TimesInt32(INT64 x, INT32 y)
{
    UINT32 x0, x1, z0, z1;
    INT64 z;
    int sign, xneg;

    /* Remember sign of result.
     */
    sign = (x.HighPart ^ y) >> 31;

    /* Take absolute values of multiplicand x and multiplier y.
     */
    xneg = (x.HighPart < 0);
    x1 = MUX(xneg, ~x.HighPart + !x.LowPart, x.HighPart);
    x0 = MUX(xneg, -x.LowPart, x.LowPart);
    y = iabs(y);

    /* Perform the unsigned 32-by-32 multiplications.
     */
    z0 = Uint32TimesUint32(x0,y);
    z1 = Uint32TimesUint32(x1,y) + umulm(x0, y);

    /* If necessary, negate product.
     */
    z.HighPart = MUX(sign, ~z1 + !z0, z1);
    z.LowPart = MUX(sign, -z0, z0);
    return (z);
}

/* MMLite runtime library function -- Multiply an unsigned,
 * 64-bit integer by an unsigned, 64-bit integer.  The
 * return value (the product) is an unsigned 64-bit integer.
 */
UINT64 Uint64TimesUint64(UINT64 x, UINT64 y)
{
    UINT64 z;

    /* Perform the unsigned 32-by-32 multiplications.
     */
    z.LowPart = Uint32TimesUint32(x.LowPart,y.LowPart);
    z.HighPart = Uint32TimesUint32(x.LowPart,y.HighPart) +
        Uint32TimesUint32(x.HighPart,y.LowPart) + umulm(x.LowPart, y.LowPart);

    return (z);
}


/* MMLite runtime library function -- Multiply an unsigned,
 * 64-bit integer by an unsigned, 32-bit integer.  The
 * return value (the product) is an unsigned 64-bit integer.
 */
UINT64 Uint64TimesUint32(UINT64 x, UINT32 y)
{
    UINT64 z;

    /* Perform the unsigned 32-by-32 multiplications.
     */
    z.LowPart = Uint32TimesUint32(x.LowPart,y);
    z.HighPart = Uint32TimesUint32(x.HighPart,y) + umulm(x.LowPart, y);

    return (z);
}