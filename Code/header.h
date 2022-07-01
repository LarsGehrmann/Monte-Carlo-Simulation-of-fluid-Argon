#ifndef header
# define header


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#define m 1 
#define sigma 1 // in reduced units
#define eps 1 // in reduced units
#include "delete_all.c"
#include "initial.c"
#include "Potential_energy.c"
#include "MC_step.c"
#include "MC_calc_all.c"

double Kinetic_energy(size_t particles, size_t dimension, double v_current[particles][3]);
void delete_all();
void initial(size_t particles, size_t dimension, int maxT, double r_current[particles][3], double v_current[particles][3], double boxlength, double temperature);
void calc_RDF(size_t particles, size_t dimension, double r_current[particles][3], double boxlength, int number_Of_Bins, double g[number_Of_Bins]);
int MC_step(size_t particles, size_t dimension, double r_current[particles][dimension], double displace, double temperature, double boxlength);
double Potential_energy(size_t particles, size_t dimension, double rmatrix[particles][dimension], double boxlength, int Particle_Number);
double MC_calc_all(size_t particles, size_t dimension, double r_current[particles][dimension], double boxlength, int number_Of_Bins, FILE* Pot, FILE* gs);


#endif