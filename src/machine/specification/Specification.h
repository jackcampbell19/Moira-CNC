#if !defined(SPECIFICATION_DEF)
#define SPECIFICATION_DEF


typedef struct {
    int z_safe_height;
    int stepper_x_stp;
    int stepper_x_dir;
    int stepper_y_stp;
    int stepper_y_dir;
    int stepper_z_stp;
    int stepper_z_dir;
} Specification;


void specification_init(Specification* spec);


#endif // SPECIFICATION_DEF
