#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double MC_calc_all(size_t particles, size_t dimension, double r_current[particles][dimension], double boxlength, int number_Of_Bins, FILE* Pot, FILE* gs)
{
	double Potential = 0;
	double g[number_Of_Bins];
	double dr = boxlength / number_Of_Bins;
	double Vol =  boxlength* boxlength* boxlength;
	double sum;
	double Delta_r[3];
	double prefactor;
	double r;
	double r2;
	double r6;
	double h[number_Of_Bins];
	double rs[number_Of_Bins];
	int idx;
	for (int j = 0; j < number_Of_Bins; j++) {
		rs[j] = (j+0.5) * dr;
		h[j] = 0;
	}
	for (int j = 0; j < particles; j++) {
		for (int kk = j + 1; kk < particles; kk++) {
			sum = 0;
			for (int iii = 0; iii < 3; iii++) {
			Delta_r[iii] = r_current[j][iii] - r_current[kk][iii];
			Delta_r[iii] -= boxlength * round(Delta_r[iii] / boxlength);
			sum += Delta_r[iii] * Delta_r[iii];
			}
			r2 = 1/sum;
			r6 = r2 * r2 * r2;
			r = sqrt(sum);
			idx = floor(r / dr);
			h[idx] += 1;
			Potential += 4 * r6 * (r6 - 1);
		}
	}
	g[0] = 0;
	for (int i = 1; i < number_Of_Bins; i++) {
		h[i] = h[i] * 2 / particles;
		g[i] = Vol * h[i] / (4 * particles * M_PI * dr * rs[i] * rs[i]);
	}
	fprintf(Pot, "%lf\n", Potential);
	fclose;
	for (int i = 0; i < number_Of_Bins; i++) {
		fprintf(gs, "%lf ", g[i]);
		fclose;
	}
	fprintf(gs, "\n");
	fclose;
} // end function
