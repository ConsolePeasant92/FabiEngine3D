# Camera scripting functions

## Setters

- `fe3d:camera_move` (`DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:camera_move_to` (`DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:camera_set_position` (`DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:camera_set_near` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_far` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_yaw` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_pitch` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_fov` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_cursor_sensitivity` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_first_person_enabled` (`BOL` value) -----> `NONE`
- `fe3d:camera_set_first_person_yaw` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_first_person_pitch` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_min_first_person_pitch` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_max_first_person_pitch` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_third_person_enabled` (`BOL` value) -----> `NONE`
- `fe3d:camera_set_third_person_yaw` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_third_person_pitch` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_min_third_person_pitch` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_max_third_person_pitch` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_third_person_distance` (`DEC` value) -----> `NONE`
- `fe3d:camera_set_third_person_lookat` (`DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:camera_set_acceleration_resistence` (`DEC` value) -----> `NONE`

## Getters

- `fe3d:camera_is_first_person_enabled` () -----> `BOL`
- `fe3d:camera_is_third_person_enabled` () -----> `BOL`
- `fe3d:camera_get_position_x` () -----> `DEC`
- `fe3d:camera_get_position_y` () -----> `DEC`
- `fe3d:camera_get_position_z` () -----> `DEC`
- `fe3d:camera_get_right_x` () -----> `DEC`
- `fe3d:camera_get_right_y` () -----> `DEC`
- `fe3d:camera_get_right_z` () -----> `DEC`
- `fe3d:camera_get_up_x` () -----> `DEC`
- `fe3d:camera_get_up_y` () -----> `DEC`
- `fe3d:camera_get_up_z` () -----> `DEC`
- `fe3d:camera_get_front_x` () -----> `DEC`
- `fe3d:camera_get_front_y` () -----> `DEC`
- `fe3d:camera_get_front_z` () -----> `DEC`
- `fe3d:camera_get_front_without_pitch_x` () -----> `DEC`
- `fe3d:camera_get_front_without_pitch_y` () -----> `DEC`
- `fe3d:camera_get_front_without_pitch_z` () -----> `DEC`
- `fe3d:camera_get_yaw` () -----> `DEC`
- `fe3d:camera_get_pitch` () -----> `DEC`
- `fe3d:camera_get_fov` () -----> `DEC`
- `fe3d:camera_get_first_person_yaw` () -----> `DEC`
- `fe3d:camera_get_first_person_pitch` () -----> `DEC`
- `fe3d:camera_get_min_first_person_pitch` () -----> `DEC`
- `fe3d:camera_get_max_first_person_pitch` () -----> `DEC`
- `fe3d:camera_get_third_person_yaw` () -----> `DEC`
- `fe3d:camera_get_third_person_pitch` () -----> `DEC`
- `fe3d:camera_get_min_third_person_pitch` () -----> `DEC`
- `fe3d:camera_get_max_third_person_pitch` () -----> `DEC`
- `fe3d:camera_get_third_person_distance` () -----> `DEC`
- `fe3d:camera_get_third_person_lookat_x` () -----> `DEC`
- `fe3d:camera_get_third_person_lookat_y` () -----> `DEC`
- `fe3d:camera_get_third_person_lookat_z` () -----> `DEC`
- `fe3d:camera_get_cursor_sensitivity` () -----> `DEC`
- `fe3d:camera_get_near` () -----> `DEC`
- `fe3d:camera_get_far` () -----> `DEC`
- `fe3d:camera_get_acceleration_resistence` () -----> `DEC`
