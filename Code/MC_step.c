int MC_step(size_t particles, size_t dimension, double r_current[particles][dimension], double displace, double temperature, double boxlength) 
{
	int Particle_number = round(ranf() * particles );
	double V_old = Potential_energy(particles , dimension , r_current , boxlength, Particle_number);
	double r_save[3];
	for (int j = 0; j < 3; j++) {
		r_save[j] = r_current[Particle_number][j];
		r_current[Particle_number][j] += (ranf() - 0.5) * displace;
	}
	double V_new = Potential_energy(particles, dimension, r_current, boxlength, Particle_number);
	double boltzmann;
	double rand_help;
	//printf("V_old: %lf, V_new: %lf ", V_old, V_new);
	if (V_new <= V_old) {
		//printf("accepted\n");
		return 1;
	}
	else 
	{
		boltzmann = exp( - (V_new - V_old) / temperature);
		rand_help = ranf();
		//printf("boltzmann: %lf,  rand_help: %lf\n", boltzmann, rand_help);
		if (rand_help <= boltzmann) {
			//printf("accepted\n");
			return 1;
		}
		else 
		{ 
			for (int j = 0; j < 3; j++)
				r_current[Particle_number][j] = r_save[j];
			//printf("denied\n");
			return 0;
		}
	}
}