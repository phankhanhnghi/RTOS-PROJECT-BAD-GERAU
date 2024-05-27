#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

void setTimer(int index, int value);
int isTimerExpired(int index);
void timerRun();
void initTimers();

#endif /* INC_SOFTWARE_TIMER_H_ */
