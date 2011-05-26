/*
 * libecb
 *
 * Copyright (©) 2009-2011 Marc Alexander Lehmann
 * Copyright (©) 2011 Emanuele Giaquinta
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modifica-
 * tion, are permitted provided that the following conditions are met:
 *
 *   1.  Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MER-
 * CHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPE-
 * CIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTH-
 * ERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ECB_H
#define ECB_H

#include <inttypes.h>

/* many compilers define _GNUC_ to some versions but then only implement
 * what their idiot authors think are the "more important" extensions,
 * causing enourmous grief for some better fake benchmark numbers or so.
 * we try to detect these and simply assume they are not gcc - if they have
 * an issue with that they should have done it right in the first place.
 */
#ifndef ECB_GCC_VERSION
# if defined(__INTEL_COMPILER) || defined(__SUNPRO_C) || defined(__llvm__)
#  define ECB_GCC_VERSION(major,minor) 0
# else
#  define ECB_GCC_VERSION(major,minor) (__GNUC__ > (major) || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor)))
# endif
#endif

#ifndef __cplusplus
# if __STDC_VERSION__ >= 199901L
#  define ECB_INLINE inline
typedef _Bool ecb_bool;
# else
#  define ECB_INLINE inline /* yeah! */
typedef int ecb_bool;
# endif
#endif

#define ECB_CONCAT_(a, b) a ## b
#define ECB_CONCAT(a, b) ECB_CONCAT_(a, b)
#define ECB_STRINGIFY_(a) # a
#define ECB_STRINGIFY(a) ECB_STRINGIFY_(a)

#define ECB_HEADER_INLINE static ECB_INLINE

#if ECB_GCC_VERSION(3,1)
# define ecb_attribute(attrlist)        __attribute__(attrlist)
# define ecb_is_constant(c)             __builtin_constant_p (c)
# define ecb_expect(expr,value)         __builtin_expect ((expr),(value))
# define ecb_prefetch(addr,rw,locality) __builtin_prefetch (addr, rw, locality)
#else
# define ecb_attribute(attrlist)
# define ecb_is_constant(c)             0
# define ecb_expect(expr,value)         (expr)
# define ecb_prefetch(addr,rw,locality)
#endif

/* no emulation for ecb_decltype */
#if ECB_GCC_VERSION(4,5)
# define ecb_decltype(x) __decltype(x)
#elif ECB_GCC_VERSION(3,0)
# define ecb_decltype(x) typeof(x)
#endif

#define ecb_noinline ecb_attribute ((noinline))
#define ecb_noreturn ecb_attribute ((noreturn))
#define ecb_unused   ecb_attribute ((unused))
#define ecb_const    ecb_attribute ((const))
#define ecb_pure     ecb_attribute ((pure))
#define ecb_hot      ecb_attribute ((hot))	/* 4.3 */
#define ecb_cold     ecb_attribute ((cold))	/* 4.3 */

/* put into ifs if you are very sure that the expression */
/* is mostly true or mosty false. note that these return */
/* booleans, not the expression. */
#define ecb_unlikely(expr) ecb_expect (!!(expr), 0)
#define ecb_likely(expr)   ecb_expect (!!(expr), 1)

/* try to tell the compiler that some condition is definitely true */
#define ecb_assume(cond) do { if (!(cond)) unreachable (); } while (0)

/* count trailing zero bits and count # of one bits */
ECB_HEADER_INLINE int ecb_ctz32      (uint32_t x) ecb_const;
ECB_HEADER_INLINE int ecb_popcount32 (uint32_t x) ecb_const;
#if ECB_GCC_VERSION(3,4)
ECB_HEADER_INLINE int ecb_ctz32      (uint32_t x) { return __builtin_ctz      (x); }
ECB_HEADER_INLINE int ecb_popcount32 (uint32_t x) { return __builtin_popcount (x); }
#else
ECB_HEADER_INLINE
ecb_ctz32 (uint32_t x)
{
  int r = 0;

  x &= -x; /* this isolates the lowest bit */

  if (x & 0xaaaaaaaa) r +=  1;
  if (x & 0xcccccccc) r +=  2;
  if (x & 0xf0f0f0f0) r +=  4;
  if (x & 0xff00ff00) r +=  8;
  if (x & 0xffff0000) r += 16;

  return r;
}

ECB_HEADER_INLINE
ecb_popcount32 (uint32_t x)
{
  x -=  (x >> 1) & 0x55555555;
  x  = ((x >> 2) & 0x33333333) + (x & 0x33333333);
  x  = ((x >> 4) + x) & 0x0f0f0f0f;
  x *= 0x01010101;

  return x >> 24;
}
#endif

ECB_HEADER_INLINE uint32_t ecb_bswap32 (uint32_t x) ecb_const;
#if ECB_GCC_VERSION(4,3)
ECB_HEADER_INLINE uint32_t ecb_bswap32 (uint32_t x) { return __builtin_bswap32 (x); }
#else
ECB_HEADER_INLINE uint32_t
ecb_bswap32 (uint32_t x)
{
  return (x >> 24)
      | ((x >>  8) & 0x0000ff00)
      | ((x <<  8) & 0x00ff0000)
      |  (x << 24);
}
#endif

ECB_HEADER_INLINE void ecb_unreachable (void) ecb_attribute ((noreturn));
#if ECB_GCC_VERSION(4,5)
ECB_HEADER_INLINE void ecb_unreachable (void) { __builtin_unreachable (); }
#else
/* this seems to work fine, but gcc always emits a warning for it :/ */
ECB_HEADER_INLINE void ecb_unreachable (void) { }
#endif

ECB_HEADER_INLINE unsigned char ecb_byteorder_helper () ecb_const;

ECB_HEADER_INLINE unsigned char
ecb_byteorder_helper ()
{
  const uint32_t u = 0x11223344;
  return *(unsigned char *)&u;
}

ECB_HEADER_INLINE ecb_bool ecb_big_endian    () ecb_const;
ECB_HEADER_INLINE ecb_bool ecb_big_endian    () { return ecb_byteorder_helper () == 0x11; };
ECB_HEADER_INLINE ecb_bool ecb_little_endian () ecb_const;
ECB_HEADER_INLINE ecb_bool ecb_little_endian () { return ecb_byteorder_helper () == 0x44; };

#if ecb_cplusplus_does_not_suck
// does not work for local types (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2657.htm)
template<typename T, int N>
static inline int ecb_array_length (const T (&arr)[N])
{
  return N;
}
#else
#define ecb_array_length(name) (sizeof (name) / sizeof (name [0]))
#endif

ECB_INLINE uint32_t ecb_rotr32 (uint32_t x, unsigned int count) ecb_const;
ECB_INLINE uint32_t
ecb_rotr32 (uint32_t x, unsigned int count)
{
  return (x << (32 - count)) | (x >> count);
}

ECB_INLINE uint32_t ecb_rotl32 (uint32_t x, unsigned int count) ecb_const;
ECB_INLINE uint32_t
ecb_rotl32 (uint32_t x, unsigned int count)
{
  return (x >> (32 - count)) | (x << count);
}

#endif

