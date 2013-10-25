#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int csymv_(char *uplo, integer *n, complex *alpha, complex *
	a, integer *lda, complex *x, integer *incx, complex *beta, complex *y,
	 integer *incy)
{
/*  -- LAPACK auxiliary routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    CSYMV  performs the matrix-vector  operation   

       y := alpha*A*x + beta*y,   

    where alpha and beta are scalars, x and y are n element vectors and   
    A is an n by n symmetric matrix.   

    Arguments   
    ==========   

    UPLO   - CHARACTER*1   
             On entry, UPLO specifies whether the upper or lower   
             triangular part of the array A is to be referenced as   
             follows:   

                UPLO = 'U' or 'u'   Only the upper triangular part of A   
                                    is to be referenced.   

                UPLO = 'L' or 'l'   Only the lower triangular part of A   
                                    is to be referenced.   

             Unchanged on exit.   

    N      - INTEGER   
             On entry, N specifies the order of the matrix A.   
             N must be at least zero.   
             Unchanged on exit.   

    ALPHA  - COMPLEX   
             On entry, ALPHA specifies the scalar alpha.   
             Unchanged on exit.   

    A      - COMPLEX array, dimension ( LDA, N )   
             Before entry, with  UPLO = 'U' or 'u', the leading n by n   
             upper triangular part of the array A must contain the upper   
             triangular part of the symmetric matrix and the strictly   
             lower triangular part of A is not referenced.   
             Before entry, with UPLO = 'L' or 'l', the leading n by n   
             lower triangular part of the array A must contain the lower   
             triangular part of the symmetric matrix and the strictly   
             upper triangular part of A is not referenced.   
             Unchanged on exit.   

    LDA    - INTEGER   
             On entry, LDA specifies the first dimension of A as declared   
             in the calling (sub) program. LDA must be at least   
             max( 1, N ).   
             Unchanged on exit.   

    X      - COMPLEX array, dimension at least   
             ( 1 + ( N - 1 )*abs( INCX ) ).   
             Before entry, the incremented array X must contain the N-   
             element vector x.   
             Unchanged on exit.   

    INCX   - INTEGER   
             On entry, INCX specifies the increment for the elements of   
             X. INCX must not be zero.   
             Unchanged on exit.   

    BETA   - COMPLEX   
             On entry, BETA specifies the scalar beta. When BETA is   
             supplied as zero then Y need not be set on input.   
             Unchanged on exit.   

    Y      - COMPLEX array, dimension at least   
             ( 1 + ( N - 1 )*abs( INCY ) ).   
             Before entry, the incremented array Y must contain the n   
             element vector y. On exit, Y is overwritten by the updated   
             vector y.   

    INCY   - INTEGER   
             On entry, INCY specifies the increment for the elements of   
             Y. INCY must not be zero.   
             Unchanged on exit.   

   =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5;
    complex q__1, q__2, q__3, q__4;
    /* Local variables */
    static integer info;
    static complex temp1, temp2;
    static integer i__, j;
    extern logical lsame_(char *, char *);
    static integer ix, iy, jx, jy, kx, ky;
    extern /* Subroutine */ int xerbla_(char *, integer *);
#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]

    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --x;
    --y;

    /* Function Body */
    info = 0;
    if (! lsame_(uplo, "U") && ! lsame_(uplo, "L")) {
	info = 1;
    } else if (*n < 0) {
	info = 2;
    } else if (*lda < max(1,*n)) {
	info = 5;
    } else if (*incx == 0) {
	info = 7;
    } else if (*incy == 0) {
	info = 10;
    }
    if (info != 0) {
	xerbla_("CSYMV ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*n == 0 || alpha->r == 0.f && alpha->i == 0.f && (beta->r == 1.f && 
	    beta->i == 0.f)) {
	return 0;
    }

/*     Set up the start points in  X  and  Y. */

    if (*incx > 0) {
	kx = 1;
    } else {
	kx = 1 - (*n - 1) * *incx;
    }
    if (*incy > 0) {
	ky = 1;
    } else {
	ky = 1 - (*n - 1) * *incy;
    }

/*     Start the operations. In this version the elements of A are   
       accessed sequentially with one pass through the triangular part   
       of A.   

       First form  y := beta*y. */

    if (beta->r != 1.f || beta->i != 0.f) {
	if (*incy == 1) {
	    if (beta->r == 0.f && beta->i == 0.f) {
		i__1 = *n;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    i__2 = i__;
		    y[i__2].r = 0.f, y[i__2].i = 0.f;
/* L10: */
		}
	    } else {
		i__1 = *n;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    i__2 = i__;
		    i__3 = i__;
		    q__1.r = beta->r * y[i__3].r - beta->i * y[i__3].i, 
			    q__1.i = beta->r * y[i__3].i + beta->i * y[i__3]
			    .r;
		    y[i__2].r = q__1.r, y[i__2].i = q__1.i;
/* L20: */
		}
	    }
	} else {
	    iy = ky;
	    if (beta->r == 0.f && beta->i == 0.f) {
		i__1 = *n;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    i__2 = iy;
		    y[i__2].r = 0.f, y[i__2].i = 0.f;
		    iy += *incy;
/* L30: */
		}
	    } else {
		i__1 = *n;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    i__2 = iy;
		    i__3 = iy;
		    q__1.r = beta->r * y[i__3].r - beta->i * y[i__3].i, 
			    q__1.i = beta->r * y[i__3].i + beta->i * y[i__3]
			    .r;
		    y[i__2].r = q__1.r, y[i__2].i = q__1.i;
		    iy += *incy;
/* L40: */
		}
	    }
	}
    }
    if (alpha->r == 0.f && alpha->i == 0.f) {
	return 0;
    }
    if (lsame_(uplo, "U")) {

/*        Form  y  when A is stored in upper triangle. */

	if (*incx == 1 && *incy == 1) {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		q__1.r = alpha->r * x[i__2].r - alpha->i * x[i__2].i, q__1.i =
			 alpha->r * x[i__2].i + alpha->i * x[i__2].r;
		temp1.r = q__1.r, temp1.i = q__1.i;
		temp2.r = 0.f, temp2.i = 0.f;
		i__2 = j - 1;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    i__3 = i__;
		    i__4 = i__;
		    i__5 = a_subscr(i__, j);
		    q__2.r = temp1.r * a[i__5].r - temp1.i * a[i__5].i, 
			    q__2.i = temp1.r * a[i__5].i + temp1.i * a[i__5]
			    .r;
		    q__1.r = y[i__4].r + q__2.r, q__1.i = y[i__4].i + q__2.i;
		    y[i__3].r = q__1.r, y[i__3].i = q__1.i;
		    i__3 = a_subscr(i__, j);
		    i__4 = i__;
		    q__2.r = a[i__3].r * x[i__4].r - a[i__3].i * x[i__4].i, 
			    q__2.i = a[i__3].r * x[i__4].i + a[i__3].i * x[
			    i__4].r;
		    q__1.r = temp2.r + q__2.r, q__1.i = temp2.i + q__2.i;
		    temp2.r = q__1.r, temp2.i = q__1.i;
/* L50: */
		}
		i__2 = j;
		i__3 = j;
		i__4 = a_subscr(j, j);
		q__3.r = temp1.r * a[i__4].r - temp1.i * a[i__4].i, q__3.i = 
			temp1.r * a[i__4].i + temp1.i * a[i__4].r;
		q__2.r = y[i__3].r + q__3.r, q__2.i = y[i__3].i + q__3.i;
		q__4.r = alpha->r * temp2.r - alpha->i * temp2.i, q__4.i = 
			alpha->r * temp2.i + alpha->i * temp2.r;
		q__1.r = q__2.r + q__4.r, q__1.i = q__2.i + q__4.i;
		y[i__2].r = q__1.r, y[i__2].i = q__1.i;
/* L60: */
	    }
	} else {
	    jx = kx;
	    jy = ky;
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = jx;
		q__1.r = alpha->r * x[i__2].r - alpha->i * x[i__2].i, q__1.i =
			 alpha->r * x[i__2].i + alpha->i * x[i__2].r;
		temp1.r = q__1.r, temp1.i = q__1.i;
		temp2.r = 0.f, temp2.i = 0.f;
		ix = kx;
		iy = ky;
		i__2 = j - 1;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    i__3 = iy;
		    i__4 = iy;
		    i__5 = a_subscr(i__, j);
		    q__2.r = temp1.r * a[i__5].r - temp1.i * a[i__5].i, 
			    q__2.i = temp1.r * a[i__5].i + temp1.i * a[i__5]
			    .r;
		    q__1.r = y[i__4].r + q__2.r, q__1.i = y[i__4].i + q__2.i;
		    y[i__3].r = q__1.r, y[i__3].i = q__1.i;
		    i__3 = a_subscr(i__, j);
		    i__4 = ix;
		    q__2.r = a[i__3].r * x[i__4].r - a[i__3].i * x[i__4].i, 
			    q__2.i = a[i__3].r * x[i__4].i + a[i__3].i * x[
			    i__4].r;
		    q__1.r = temp2.r + q__2.r, q__1.i = temp2.i + q__2.i;
		    temp2.r = q__1.r, temp2.i = q__1.i;
		    ix += *incx;
		    iy += *incy;
/* L70: */
		}
		i__2 = jy;
		i__3 = jy;
		i__4 = a_subscr(j, j);
		q__3.r = temp1.r * a[i__4].r - temp1.i * a[i__4].i, q__3.i = 
			temp1.r * a[i__4].i + temp1.i * a[i__4].r;
		q__2.r = y[i__3].r + q__3.r, q__2.i = y[i__3].i + q__3.i;
		q__4.r = alpha->r * temp2.r - alpha->i * temp2.i, q__4.i = 
			alpha->r * temp2.i + alpha->i * temp2.r;
		q__1.r = q__2.r + q__4.r, q__1.i = q__2.i + q__4.i;
		y[i__2].r = q__1.r, y[i__2].i = q__1.i;
		jx += *incx;
		jy += *incy;
/* L80: */
	    }
	}
    } else {

/*        Form  y  when A is stored in lower triangle. */

	if (*incx == 1 && *incy == 1) {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		q__1.r = alpha->r * x[i__2].r - alpha->i * x[i__2].i, q__1.i =
			 alpha->r * x[i__2].i + alpha->i * x[i__2].r;
		temp1.r = q__1.r, temp1.i = q__1.i;
		temp2.r = 0.f, temp2.i = 0.f;
		i__2 = j;
		i__3 = j;
		i__4 = a_subscr(j, j);
		q__2.r = temp1.r * a[i__4].r - temp1.i * a[i__4].i, q__2.i = 
			temp1.r * a[i__4].i + temp1.i * a[i__4].r;
		q__1.r = y[i__3].r + q__2.r, q__1.i = y[i__3].i + q__2.i;
		y[i__2].r = q__1.r, y[i__2].i = q__1.i;
		i__2 = *n;
		for (i__ = j + 1; i__ <= i__2; ++i__) {
		    i__3 = i__;
		    i__4 = i__;
		    i__5 = a_subscr(i__, j);
		    q__2.r = temp1.r * a[i__5].r - temp1.i * a[i__5].i, 
			    q__2.i = temp1.r * a[i__5].i + temp1.i * a[i__5]
			    .r;
		    q__1.r = y[i__4].r + q__2.r, q__1.i = y[i__4].i + q__2.i;
		    y[i__3].r = q__1.r, y[i__3].i = q__1.i;
		    i__3 = a_subscr(i__, j);
		    i__4 = i__;
		    q__2.r = a[i__3].r * x[i__4].r - a[i__3].i * x[i__4].i, 
			    q__2.i = a[i__3].r * x[i__4].i + a[i__3].i * x[
			    i__4].r;
		    q__1.r = temp2.r + q__2.r, q__1.i = temp2.i + q__2.i;
		    temp2.r = q__1.r, temp2.i = q__1.i;
/* L90: */
		}
		i__2 = j;
		i__3 = j;
		q__2.r = alpha->r * temp2.r - alpha->i * temp2.i, q__2.i = 
			alpha->r * temp2.i + alpha->i * temp2.r;
		q__1.r = y[i__3].r + q__2.r, q__1.i = y[i__3].i + q__2.i;
		y[i__2].r = q__1.r, y[i__2].i = q__1.i;
/* L100: */
	    }
	} else {
	    jx = kx;
	    jy = ky;
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = jx;
		q__1.r = alpha->r * x[i__2].r - alpha->i * x[i__2].i, q__1.i =
			 alpha->r * x[i__2].i + alpha->i * x[i__2].r;
		temp1.r = q__1.r, temp1.i = q__1.i;
		temp2.r = 0.f, temp2.i = 0.f;
		i__2 = jy;
		i__3 = jy;
		i__4 = a_subscr(j, j);
		q__2.r = temp1.r * a[i__4].r - temp1.i * a[i__4].i, q__2.i = 
			temp1.r * a[i__4].i + temp1.i * a[i__4].r;
		q__1.r = y[i__3].r + q__2.r, q__1.i = y[i__3].i + q__2.i;
		y[i__2].r = q__1.r, y[i__2].i = q__1.i;
		ix = jx;
		iy = jy;
		i__2 = *n;
		for (i__ = j + 1; i__ <= i__2; ++i__) {
		    ix += *incx;
		    iy += *incy;
		    i__3 = iy;
		    i__4 = iy;
		    i__5 = a_subscr(i__, j);
		    q__2.r = temp1.r * a[i__5].r - temp1.i * a[i__5].i, 
			    q__2.i = temp1.r * a[i__5].i + temp1.i * a[i__5]
			    .r;
		    q__1.r = y[i__4].r + q__2.r, q__1.i = y[i__4].i + q__2.i;
		    y[i__3].r = q__1.r, y[i__3].i = q__1.i;
		    i__3 = a_subscr(i__, j);
		    i__4 = ix;
		    q__2.r = a[i__3].r * x[i__4].r - a[i__3].i * x[i__4].i, 
			    q__2.i = a[i__3].r * x[i__4].i + a[i__3].i * x[
			    i__4].r;
		    q__1.r = temp2.r + q__2.r, q__1.i = temp2.i + q__2.i;
		    temp2.r = q__1.r, temp2.i = q__1.i;
/* L110: */
		}
		i__2 = jy;
		i__3 = jy;
		q__2.r = alpha->r * temp2.r - alpha->i * temp2.i, q__2.i = 
			alpha->r * temp2.i + alpha->i * temp2.r;
		q__1.r = y[i__3].r + q__2.r, q__1.i = y[i__3].i + q__2.i;
		y[i__2].r = q__1.r, y[i__2].i = q__1.i;
		jx += *incx;
		jy += *incy;
/* L120: */
	    }
	}
    }

    return 0;

/*     End of CSYMV */

} /* csymv_ */

#undef a_ref
#undef a_subscr

