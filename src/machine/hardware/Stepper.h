#if !defined(STEPPER_DEF)
#define STEPPER_DEF


typedef struct {
    int stp;
    int dir;
} Stepper;


void stepper_construct(Stepper* stepper, int stp, int dir);
void stepper_step(Stepper* stepper, int direction);


#endif // STEPPER_DEF
