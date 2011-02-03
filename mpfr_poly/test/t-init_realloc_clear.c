/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/****************************************************************************

   Copyright (C) 2010 William Hart

*****************************************************************************/

#include <stdio.h>
#include <mpir.h>
#include <mpfr.h>
#include "flint.h"
#include "mpfr_poly.h"
#include "ulong_extras.h"

int main(void)
{
   int result = 0;
   flint_rand_t state;
   ulong i;

   printf("init/init2/realloc/clear....");
   fflush(stdout);

   flint_randinit(state);
   
   for (i = 0; i < 10000UL; i++) 
   {
      mpfr_poly_t a;

      mpfr_poly_init(a, n_randint(state, 100)+ MPFR_PREC_MIN);
      mpfr_poly_clear(a);      
   }
   
   for (i = 0; i < 10000UL; i++) 
   {
      mpfr_poly_t a;

      mpfr_poly_init2(a, n_randint(state, 100), n_randint(state, 100) + MPFR_PREC_MIN);
      mpfr_poly_realloc(a, n_randint(state, 100));
      mpfr_poly_realloc(a, n_randint(state, 100));
      mpfr_poly_clear(a);
   }
   
   for (i = 0; i < 10000UL; i++) 
   {
      mpfr_poly_t a;
      ulong prec = n_randint(state, 100) + MPFR_PREC_MIN;

      mpfr_poly_init(a, prec);
      mpfr_poly_randtest(a, state, n_randint(state, 100));
      
      mpfr_poly_clear(a);
   }
   
   flint_randclear(state);
      
   printf("PASS\n");
   return result;
}
