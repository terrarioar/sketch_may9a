#include "Motor.h"

Motor::Motor() {

};

Motor::Motor(int in, int out) {
	inpin = in;
	outpin = out;
};

Motor::~Motor() {

};

void Motor::setStatus(bool dir1,int time1) {
	dir = dir1;
	times = time1;
}
