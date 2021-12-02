/* The purpose of this file is to generate a non-inlined version of
 * mathutil_vec_cross_prod, which is called indirectly by lbl_8003781C due to
 * the inlining depth limit. That non-inlined version would normally be placed
 * immediately after lbl_8003781C, but the original code places it at the very
 * end of ball.c. This file is linked immediately after ball.c and generates a
 * a non-inlined version of mathutil_vec_cross_prod that overrides the one
 * generated by ball.c.
 */
#include <dolphin.h>
#define inline  // remove the inline keyword from all mathutil.h functions
#include "mathutil.h"
