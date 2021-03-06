#include "fft_fftw.hh"

fft_fftw::fft_fftw(int nin)
  :n(nin)
{
	double *f = (double *)_mm_malloc(2*n*sizeof(double), 32);
	fftw_complex *ff  = (fftw_complex *)f;
	pf = fftw_plan_dft_1d(n, ff, ff, -1, FFTW_MEASURE);
	pb = fftw_plan_dft_1d(n, ff, ff,  1, FFTW_MEASURE);
	_mm_free(f);
}

fft_fftw::~fft_fftw(){
	fftw_destroy_plan(pf);
	fftw_destroy_plan(pb);
}

