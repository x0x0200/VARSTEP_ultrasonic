#include <VARSTEP_ultrasonic.h>

VARSTEP_ultrasonic::VARSTEP_ultrasonic(int trigger_pin, int echo_pin) {
	this -> trigger_pin = trigger_pin;
	this -> echo_pin = echo_pin;
	pinMode(trigger_pin, OUTPUT);
	pinMode(echo_pin, INPUT);
}

double VARSTEP_ultrasonic::distance_cm() {
	digitalWrite(trigger_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigger_pin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigger_pin, LOW);

	unsigned long wave_response_micro_seconds = pulseIn(echo_pin, HIGH);
	double distance_cm = (wave_response_micro_seconds * 0.0343) / 2.0;

	if(distance_cm == 0 || distance_cm > 400) 
		return - 1.0;
	else
		return distance_cm;
}

double VARSTEP_ultrasonic::distance_m() {
	double distance_cm = VARSTEP_ultrasonic::distance_cm();
	return distance_cm  == -1.0 ? -1.0 : distance_cm / 100.0;
}