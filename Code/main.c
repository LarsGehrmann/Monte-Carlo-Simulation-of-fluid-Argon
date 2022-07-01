#include "header.h"
void main()
{
	clock_t begin = clock();
	delete_all();
	FILE* Pot = NULL;
	FILE* gs = NULL;
	Pot = fopen("./data/Pot.txt", "a");
	gs = fopen("./data/gs.txt", "a");
	double temperature = 94.4 /119.8 ;
	int Timesteps = 10000;
	int n_sample = 100;
	int data_points = Timesteps / n_sample;
	double displace = 0.28;
	size_t particles = 1000;
	double rho = 1.374;	// in g/cm^3
	double third = 1.0 / 3.0;
	double boxlength = pow(particles * 6.635 * 10 / ( pow(3.405,3) *  rho),third);
	printf("boxlength %lf\n", boxlength);
	int number_Of_Bins = 100;
	int accept;
	double accept_avg = 0;
	size_t dimension = 3;
	double r_current[particles][3];
	double v_current[particles][3];
	int counter = 0;
	initial(particles, dimension, Timesteps, r_current, v_current, boxlength,temperature);
	for (int k = 0; k < Timesteps; k++) {
		accept = MC_step(particles, dimension, r_current, displace, temperature, boxlength);
		accept_avg += accept;
		 if (k % n_sample == 0) {
			MC_calc_all(particles, dimension, r_current, boxlength, number_Of_Bins, Pot, gs);
		} 
		 if (k % 100000 == 0) {
			 printf("%d\n", k);
			 double acc_help = accept_avg / k;
			// printf("Current acceptance rate: %lf", acc_help);
		 }
	}
	accept_avg = accept_avg / Timesteps;
	printf("accept_avg: %lf   displace: %lf   Timesteps: %d \n", accept_avg, displace, Timesteps);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Total time needed: %lfs\n", time_spent);
} // end main