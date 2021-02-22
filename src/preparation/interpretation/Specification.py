import json

file = open('../../../config.json')
specs = json.load(file)['specification']

# Hard values
motor_steps_per_rotation = int(specs['steps-per-rotation'])
lead_screw_linear_motion_per_rotation = int(specs['lead-screw-linear-motion-per-rotation'])
points_per_mm = float(specs['points-per-mm'])

file.close()

# Computed values
linear_motion_per_motor_step = lead_screw_linear_motion_per_rotation / motor_steps_per_rotation  # mm
points_per_step = linear_motion_per_motor_step * points_per_mm


def points_to_steps(p):
    if p is None or type(p) is str and len(p) == 0:
        return 0
    p = float(p)
    return int(round(p / points_per_step))
