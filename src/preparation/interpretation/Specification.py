import json

# Hard values
motor_steps_per_rotation = 200
lead_screw_linear_motion_per_rotation = 8
points_per_mm = 2.83465

# Computed values
linear_motion_per_motor_step = lead_screw_linear_motion_per_rotation / motor_steps_per_rotation  # mm
points_per_step = linear_motion_per_motor_step * points_per_mm


def points_to_steps(p):
    if p is None or type(p) is str and len(p) == 0:
        return 0
    p = float(p)
    return int(round(p / points_per_step))
