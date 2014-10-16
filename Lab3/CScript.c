FILE *period;
FILE *duty;
FILE *run;

int main() {

	// Do it once to setup period and run modes 
	period = fopen("/sys/devices/ocp.3/pwm_test_P9_14.16/period","w");
	duty = fopen("/sys/devices/ocp.3/pwm_test_P9_14.16/duty","w");
	run = fopen("/sys/devices/ocp.3/pwm_test_P9_14.16/run","w");

	fprintf(period,"500000");
	fprintf(duty,"0");
	fprintf(run,"1");

	fclose(period);
	fclose(duty);
	fclose(run);

	while(1) {
		// Change duty cycle
		duty = fopen("/sys/devices/ocp.3/pwm_test_P9_14.16/duty","w");
		fprintf(duty,"125000");
		fclose(duty);
		
		usleep(1000000);

		// Change duty cycle
		duty = fopen("/sys/devices/ocp.3/pwm_test_P9_14.16/duty","w");
		fprintf(duty,"250000");
		fclose(duty);

		usleep(1000000);

		// Change duty cycle
		duty = fopen("/sys/devices/ocp.3/pwm_test_P9_14.16/duty","w");
		fprintf(duty,"375000");
		fclose(duty);

		usleep(1000000);

		// Change duty cycle
		duty = fopen("/sys/devices/ocp.3/pwm_test_P9_14.16/duty","w");
		fprintf(duty,"500000");
		fclose(duty);

		usleep(1000000);

	}
}

