#include <iostream>
#include <math.h>
#include <tuple>

using namespace std;

struct Gaussian
{
	double mean;
	double var;
};

void filter(Gaussian* prior, Gaussian* measurement, Gaussian* motion)
{
	// update this state by taking into account measurement information
	prior->mean = ((measurement->mean * prior->var)
		              + (prior->mean * measurement->var))
	                / (prior->var + measurement->var);
	prior->var = 1 / (1 / prior->var + 1 / measurement->var);
	printf("Update in position from measurement info ");
	printf("(measurement update): %.2f, %.2f\n", prior->mean, prior->var);

	// predict new state from prior and motion
	prior->mean = prior->mean + motion->mean;
	prior->var = prior->var + motion->var;
	printf("Update in position from executed motion ");
	printf("(state prediction): %.2f, %.2f\n", prior->mean, prior->var);

}
