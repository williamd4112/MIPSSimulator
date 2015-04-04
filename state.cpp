#include "state.h"

const char *WRITE_REGZERO_MSG = "Write $0 Error";
const char *NUMBER_OVERFLOW_MSG = "Number Overflow";
const char *ADDRESS_OVERFLOW_MSG = "Address Overflow";
const char *DATA_MISALIGN_MSG = "Misalignment Error";

int STATE = ENABLE, CYCLE = 0, ERROR = 0;

// ****** Preserved for multiple same errors in one cycle *****
// std::priority_queue<int, std::vector<int>, std::greater<int> >error_msg_queue;

void error(int errorid){
	ERROR = (errorid == WRITE_REGZERO ||
	   		errorid == NUMBER_OVERFLOW ||
	   		errorid == ADDRESS_OVERFLOW ||
	   		errorid == DATA_MISALIGN) ? ERROR | errorid : ERROR;

	if(ERROR & (ADDRESS_OVERFLOW | DATA_MISALIGN)) 
		STATE = INTERRUPT;
}

// Print error message
void print_error(){
	if(ERROR & WRITE_REGZERO) 
		fprintf(stderr, "In cycle %d: %s\n", CYCLE, WRITE_REGZERO_MSG);
	if(ERROR & NUMBER_OVERFLOW) 
		fprintf(stderr, "In cycle %d: %s\n", CYCLE, NUMBER_OVERFLOW_MSG);
	if(ERROR & ADDRESS_OVERFLOW) 
		fprintf(stderr, "In cycle %d: %s\n", CYCLE, ADDRESS_OVERFLOW_MSG);
	if(ERROR & DATA_MISALIGN) 
		fprintf(stderr, "In cycle %d: %s\n", CYCLE, DATA_MISALIGN_MSG);
	ERROR = 0;
}


// ****** Preserved for multiple same errors in one cycle *****
/*
void print_error(){
	while(!error_msg_queue.empty()){
		int errorid = error_msg_queue.top();
		switch(errorid){
			case WRITE_REGZERO:
				fprintf(stderr, "In cycle %d: %s\n", CYCLE, WRITE_REGZERO_MSG);
				break;
			case NUMBER_OVERFLOW:
				fprintf(stderr, "In cycle %d: %s\n", CYCLE, NUMBER_OVERFLOW_MSG);
				break;
			case ADDRESS_OVERFLOW:
				fprintf(stderr, "In cycle %d: %s\n", CYCLE, ADDRESS_OVERFLOW_MSG);
				STATE = INTERRUPT;
				break;
			case DATA_MISALIGN:
				fprintf(stderr, "In cycle %d: %s\n", CYCLE, DATA_MISALIGN_MSG);
				STATE = INTERRUPT;
				break;
			default: // Unknown error
				break;
		}
		error_msg_queue.pop();
	}
}*/