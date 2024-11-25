# MAVLink message: MAVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS
# https://mavlink.io/en/messages/common.html#MAVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS

std_msgs/Header header

uint16 device_flags   # Current gimbal flags set

uint16 DEVICE_FLAGS_RETRACT = 1
uint16 DEVICE_FLAGS_NEUTRAL = 2
uint16 DEVICE_FLAGS_ROLL_LOCK = 4
uint16 DEVICE_FLAGS_PITCH_LOCK = 8
uint16 DEVICE_FLAGS_YAW_LOCK = 16

float32[4] q               # Quaternion components, w, x, y, z (1 0 0 0 is the null-rotation, the frame is depends on whether the flag GIMBAL_DEVICE_FLAGS_YAW_LOCK is set)
float32 angular_velocity_x # [rad/s] X component of angular velocity (NaN if unknown)
float32 angular_velocity_y # [rad/s] Y component of angular velocity (NaN if unknown)
float32 angular_velocity_z # [rad/s] Z component of angular velocity (NaN if unknown)

uint32 failure_flags       #  Failure flags (0 for no failure)