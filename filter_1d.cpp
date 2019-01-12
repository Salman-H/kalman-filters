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

int main()
{
	Gaussian prior;
	Gaussian measurement;
	Gaussian motion;

	string mystr;

	// Test filter with data from a mobile robot

	cout << "Enter the variance in robot position from sensor measurements: ";
	getline(cin, mystr);
	stringstream(mystr) >> measurement.var;

	cout << "Enter the variance in robot position from its motion: ";
	getline(cin, mystr);
	stringstream(mystr) >> motion.var;

	cout << "Enter the initial estimate for mean position: ";
	getline(cin, mystr);
	stringstream(mystr) >> prior.mean;

	cout << "Enter initial estimate for variance in this position: ";
	getline(cin, mystr);
	stringstream(mystr) >> prior.var;

	int N;
	cout << "Enter the number of Kalman filter iterations: ";
	getline(cin, mystr);
	stringstream(mystr) >> N;

	for (int i=0; i<N; i++) 
	{
		cout << "Enter the mean position reported from sensor measurement: ";
		getline(cin, mystr);
		stringstream(mystr) >> measurement.mean;

		cout << "Enter the mean position after executed motion: ";
		getline(cin, mystr);
		stringstream(mystr) >> motion.mean;

		// Apply Kalman filter to get best estimate of current position
		filter(&prior, &measurement, &motion);

		// and see if it converges at the robot's true position
		printf("Best estimate of current position and its confidence: "); 
		printf("%.2f, %.2f\n\n", prior.mean, prior.var);
	}

}
