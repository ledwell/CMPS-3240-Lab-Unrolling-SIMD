#include <immintrin.h>
// If windows: #include <x86intrin.h>
#include "myblas.h"

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
