#if !defined(STEPPER_DEF)
#define STEPPER_DEF

struct Stepper_ {
    int stp;
    int dir;
};
typedef struct Stepper_ Stepper;

void stepper_construct(Stepper* stepper, int stp, int dir);
void stepper_step(Stepper* stepper, int direction);

#endif // STEPPER_DEF
