/* PR c/2098 */
/* Test for a warning on comparison on out-of-range data.  */
/* { dg-do compile } */
/* { dg-xfail-if "" { c4x-*-* } { "*" } { "" } } */
/* { dg-options "-Wtype-limits" } */

signed char sc;
unsigned char uc;

void foo()
{
  if (sc == 10000) return; /* { dg-warning "always false" "signed" } */
  if (uc == 10000) return; /* { dg-warning "always false" "unsigned" } */
}
