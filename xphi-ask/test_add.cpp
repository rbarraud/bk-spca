#include <iostream>

extern void init_manycore_cheap(double *list, long len, int nthreads, 
				double x);

extern double sum_manycore(double *list, long len, int nthreads);


double find_sum(int nthreads, double x){
	long nbytes = 4l*1000*1000*1000;
	
	double *list = (double *)_mm_malloc(nbytes, 64);
	long len = nbytes/8;

	init_manycore_cheap(list, len, nthreads, x);
	double ans = sum_manycore(list, len, nthreads);

	_mm_free(list);
	return ans;
}

int main(){
	const int niters = 20;
#ifdef __MIC__
	int nthreads = 244;
#else
	int nthreads = 16;
#endif
	double sum = 0;
	for(int i=0; i < niters; i++){
		std::cout<<i<<std::endl;
		sum += find_sum(nthreads, (i+1.0));
	}

	std::cout<<"           computed sum = "<<sum<<std::endl;
	std::cout<<"nbytes implied by above = "<<sum/(niters+1)/niters*16
		 <<std::endl;
}