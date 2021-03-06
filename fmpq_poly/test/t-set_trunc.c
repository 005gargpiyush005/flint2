/*=============================================================================

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

=============================================================================*/
/******************************************************************************

    Copyright (C) 2014 Fredrik Johansson

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("set_trunc....");
    fflush(stdout);

    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        fmpq_poly_t a, b, c;
        slong n;

        fmpq_poly_init(a);
        fmpq_poly_init(b);
        fmpq_poly_init(c);

        fmpq_poly_randtest(a, state, n_randint(state, 100), 200);
        fmpq_poly_randtest(b, state, n_randint(state, 100), 200);
        n = n_randint(state, 50);

        fmpq_poly_set_trunc(b, a, n);
        fmpq_poly_set(c, a);
        fmpq_poly_truncate(c, n);

        result = (fmpq_poly_equal(b, c));
        if (!result)
        {
            flint_printf("FAIL:\n");
            fmpq_poly_print(a), flint_printf("\n\n");
            fmpq_poly_print(b), flint_printf("\n\n");
            fmpq_poly_print(c), flint_printf("\n\n");
            abort();
        }

        fmpq_poly_set_trunc(a, a, n);

        result = (fmpq_poly_equal(a, c));
        if (!result)
        {
            flint_printf("FAIL (aliasing):\n");
            fmpq_poly_print(a), flint_printf("\n\n");
            fmpq_poly_print(c), flint_printf("\n\n");
            abort();
        }

        fmpq_poly_clear(a);
        fmpq_poly_clear(b);
        fmpq_poly_clear(c);
    }

    FLINT_TEST_CLEANUP(state);
    flint_printf("PASS\n");
    return 0;
}
