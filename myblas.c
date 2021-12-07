#include <immintrin.h>
// If windows: #include <x86intrin.h>
#include "myblas.h"

/* DGEMM. From Computer Organization and Design, Patterson and Hennesey 5e
 * An unoptimized version of a double precision matrix multiplication, widely
 * known as 'DGEMM' for double-precision general matrix multiply (GEMM). 
 * Assumes matrixes are square and of the same length ('n' is the length of 
 * one side).
 *
 * This example differs from the book because it uses SSE intrinsics rather 
 * than AVX intrinsics. AVX intrinsics are newer and there is a risk that some
 * users might not have it. For example, 'sleipnir.cs.csubak.edu' does not have
 * AVX.
 */
void fgemmo( int n, float* A, float* B, float* C ) {
    for ( int i = 0; i < n; i+=4) {
        for ( int j = 0; j < n; j++ ) {
            //double cij = C[ i + j * n ]; replaced with:
            __m128 cij = _mm_loadu_ps(C + i + j * n);
            /* __m128: A data type that tells the compiler to put the data in
             * a 128-bit mm register, packed with four 32-bit single precision
             * floating point values. __m128d is the type for packing two 64-bit
             * double precision floating point values. __m128i is the type of 
             * packing four 32-bit integers. This notation is also used for 
             * prefixing the operations that use these types. 
             * 
             * _mm_loadu_ps loads four successive values from the array into
             * an mm register. loadu indicates it's a load operation. load
             * (rather than loadu) is used for Windows. _ps indicates that the
             * operation is for single precision. _pd indicates an operation
             * that is double precision.
             */

            // Below carries out cij += A[i][k] * B[k][j]:
            for ( int k = 0; k < n; k++) {
		float d = B[k+j*n];
                // cij += A[ i + k * n ] * B[ k + j * n ];
                // ... replaced with:
                cij = _mm_add_ps(
                    cij, // +=
                    _mm_mul_ps(
                        _mm_loadu_ps(A + i + k * n),
                        _mm_set_ps1(d)
                    )
                );
                /* _mm128_set_ps1 broadcasts a single value to four positions
                 * in a mm register. 
                 */
            }
            //C[ i + j * n ] = cij; replaced with
            _mm_storeu_ps(&C[ i + j * n ], cij);
        }
    }
}

// Unoptimized version
void fgemmu( int n, float* A, float* B, float* C ) {
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < n; j++ ) {
            double cij = C[ i + j * n ]; 

            for ( int k = 0; k < n; k++) {
                cij += A[ i + k * n ] * B[ k + j * n ];
            }

            C[ i + j * n ] = cij; 
        }
    }
}

// FAXPY operation. Not optimized with AVX intrinsics.
void faxpy1( int n, float A, float* x, float* y, float* result ) {
    for( int i = 0; i < n; i++ )
        result[i] = A * x[i] + y[i];
        
}

void faxpy2( int n, float A, float* x, float* y, float* result ) {
	for( int i = 0; i < n; i+=3) {
		result[i] = A * x[i] + y[i];
		result[i+1] = A * x[i+1] + y[i+1];
		result[i+2] = A * x[i+2] + y[i+2];
	}
}

void faxpy3( int n, float A, float* x, float* y, float* result ) {
    for(int i = 0; i < n; i+=4 ) {
        _mm_storeu_ps( &result[ i ] , 
                _mm_add_ps(
                    _mm_mul_ps(
                        _mm_set_ps1(A),// vbroadcast version of A,
                        _mm_loadu_ps( x + i)// x[i]
                        ),
                        _mm_loadu_ps( y + i)
                    )
                );
        // result[i] = A * x[i] + y[i];
    }
}

void faxpy4( int n, float A, float* x, float* y, float* result) {
	for (int i = 0; i < n; i+=8 ) {
		_mm_storeu_ps( &result[ i ] , 
                _mm_add_ps(
                    _mm_mul_ps(
                        _mm_set_ps1(A),// vbroadcast version of A,
                        _mm_loadu_ps( x + i)// x[i]
                        ),
                        _mm_loadu_ps( y + i)
                    )
                );
		_mm_storeu_ps ( &result [ (i + 4) ] ,
			_mm_add_ps(
				_mm_mul_ps(
					_mm_set_ps1(A),
					_mm_loadu_ps( x + (i + 4))
					),
					_mm_loadu_ps( y + (i + 4))
				)
			);
	}
}

void faxpy5( int n, float A, float* x, float* y, float* result ) {
	for( int i = 0; i < n; i+=4) {
		result[i] = A * x[i] + y[i];
		result[i+1] = A * x[i+1] + y[i+1];
		result[i+2] = A * x[i+2] + y[i+2];
		result[i+3] = A * x[i+3] + y[i+3];
	}
}

void faxpy6( int n, float A, float* x, float* y, float* result ) {
	for( int i = 0; i < n; i+=5) {
		result[i] = A * x[i] + y[i];
		result[i+1] = A * x[i+1] + y[i+1];
		result[i+2] = A * x[i+2] + y[i+2];
		result[i+3] = A * x[i+3] + y[i+3];
		result[i+4] = A * x[i+4] + y[i+4];
	}
}

void faxpy7( int n, float A, float* x, float* y, float* result ) {
	for( int i = 0; i < n; i+=6) {
		result[i] = A * x[i] + y[i];
		result[i+1] = A * x[i+1] + y[i+1];
		result[i+2] = A * x[i+2] + y[i+2];
		result[i+3] = A * x[i+3] + y[i+3];
		result[i+4] = A * x[i+4] + y[i+4];
		result[i+5] = A * x[i+5] + y[i+5];
	}
}

void faxpy8( int n, float A, float* x, float* y, float* result ) {
	for( int i = 0; i < n; i+=7) {
		result[i] = A * x[i] + y[i];
		result[i+1] = A * x[i+1] + y[i+1];
		result[i+2] = A * x[i+2] + y[i+2];
		result[i+3] = A * x[i+3] + y[i+3];
		result[i+4] = A * x[i+4] + y[i+4];
		result[i+5] = A * x[i+5] + y[i+5];
		result[i+6] = A * x[i+6] + y[i+6];
	}
}

void faxpy9( int n, float A, float* x, float* y, float* result ) {
	for( int i = 0; i < n; i+=8) {
		result[i] = A * x[i] + y[i];
		result[i+1] = A * x[i+1] + y[i+1];
		result[i+2] = A * x[i+2] + y[i+2];
		result[i+3] = A * x[i+3] + y[i+3];
		result[i+4] = A * x[i+4] + y[i+4];
		result[i+5] = A * x[i+5] + y[i+5];
		result[i+6] = A * x[i+6] + y[i+6];
		result[i+7] = A * x[i+7] + y[i+7];
	}
}

void faxpy10( int n, float A, float* x, float* y, float* result ) {
	for( int i = 0; i < n; i+=9) {
		result[i] = A * x[i] + y[i];
		result[i+1] = A * x[i+1] + y[i+1];
		result[i+2] = A * x[i+2] + y[i+2];
		result[i+3] = A * x[i+3] + y[i+3];
		result[i+4] = A * x[i+4] + y[i+4];
		result[i+5] = A * x[i+5] + y[i+5];
		result[i+6] = A * x[i+6] + y[i+6];
		result[i+7] = A * x[i+7] + y[i+7];
		result[i+8] = A * x[i+8] + y[i+8];
	}
}

void faxpy11( int n, float A, float* x, float* y, float* result ) {
	for( int i = 0; i < n; i+=10) {
		result[i] = A * x[i] + y[i];
		result[i+1] = A * x[i+1] + y[i+1];
		result[i+2] = A * x[i+2] + y[i+2];
		result[i+3] = A * x[i+3] + y[i+3];
		result[i+4] = A * x[i+4] + y[i+4];
		result[i+5] = A * x[i+5] + y[i+5];
		result[i+6] = A * x[i+6] + y[i+6];
		result[i+7] = A * x[i+7] + y[i+7];
		result[i+8] = A * x[i+8] + y[i+8];
		result[i+9] = A * x[i+9] + y[i+9];
	}
}

void faxpy12( int n, float A, float* x, float* y, float* result ) {
	for( int i = 0; i < n; i+=11) {
		result[i] = A * x[i] + y[i];
		result[i+1] = A * x[i+1] + y[i+1];
		result[i+2] = A * x[i+2] + y[i+2];
		result[i+3] = A * x[i+3] + y[i+3];
		result[i+4] = A * x[i+4] + y[i+4];
		result[i+5] = A * x[i+5] + y[i+5];
		result[i+6] = A * x[i+6] + y[i+6];
		result[i+7] = A * x[i+7] + y[i+7];
		result[i+8] = A * x[i+8] + y[i+8];
		result[i+9] = A * x[i+9] + y[i+9];
		result[i+10] = A * x[i+10] + y[i+10];
	}
}