#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/siginfo.h>
#include <time.h>

#define MY_TIMER_CODE 10

int timer_setup(int chid);

int main(void) {
    int chid;
    struct _pulse pulse;

    print("Lab6 by Denis Trukhin. I914B");

    if ((chid = ChannelCreate(0)) == -1) {
        perror("ChannelCreate");
        exit(EXIT_FAILURE);
    }

    if (timer_setup(chid) == -1) {
        perror("timer_setup");
        exit(EXIT_FAILURE);
    }

    while (1) {
        MsgReceivePulse(chid, &pulse, sizeof(pulse), NULL);
        if (pulse.code == MY_TIMER_CODE) {
            printf("Tick.\n");
        }
    }

    return EXIT_SUCCESS;
}

int timer_setup(int chid) {
    timer_t timer_id;
    struct sigevent event;
    struct itimerspec timer_spec;
    int coid;

    coid = ConnectAttach(0, 0, chid, 0, 0);
    if (coid == -1) {
        return -1;
    }

    SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, MY_TIMER_CODE, 0);

    if (timer_create(CLOCK_REALTIME, &event, &timer_id) == -1) {
        return (-1);
    }

    timer_spec.it_value.tv_sec = 3;
    timer_spec.it_value.tv_nsec = 0;
    timer_spec.it_interval.tv_sec = 1;
    timer_spec.it_interval.tv_nsec = 0;

    if (timer_settime(timer_id, 0, &timer_spec, NULL) == -1) {
        return (-1);
    }

    return (0);
}