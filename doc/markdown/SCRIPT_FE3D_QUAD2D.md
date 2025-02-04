# Quad2D scripting functions

## Setters

- `fe3d:quad2d_place` (`STR` new_id, `STR` editor_id, `DEC` position_x, `DEC` position_y, `DEC` size_x, `DEC` size_y) -----> `NONE`
- `fe3d:quad2d_delete` (`STR` quad_id) -----> `NONE`
- `fe3d:quad2d_delete_all` () -----> `NONE`
- `fe3d:quad2d_move` (`STR` quad_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:quad2d_rotate` (`STR` quad_id, `DEC` value) -----> `NONE`
- `fe3d:quad2d_scale` (`STR` quad_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:quad2d_move_to` (`STR` quad_id, `DEC` target_x, `DEC` target_y, `DEC` speed) -----> `NONE`
- `fe3d:quad2d_rotate_to` (`STR` quad_id, `DEC` target, `DEC` speed) -----> `NONE`
- `fe3d:quad2d_scale_to` (`STR` quad_id, `DEC` target_x, `DEC` target_y, `DEC` speed) -----> `NONE`
- `fe3d:quad2d_start_animation2d` (`STR` quad_id, `STR` animation_id, `INT` play_count) -----> `NONE`
- `fe3d:quad2d_pause_animation2d` (`STR` quad_id, `STR` animation_id) -----> `NONE`
- `fe3d:quad2d_autopause_animation2d` (`STR` quad_id, `STR` animation_id) -----> `NONE`
- `fe3d:quad2d_resume_animation2d` (`STR` quad_id, `STR` animation_id) -----> `NONE`
- `fe3d:quad2d_stop_animation2d` (`STR` quad_id, `STR` animation_id) -----> `NONE`
- `fe3d:quad2d_set_visible` (`STR` quad_id, `BOL` value) -----> `NONE`
- `fe3d:quad2d_set_diffuse_map` (`STR` quad_id, `STR` file_path) -----> `NONE`
- `fe3d:quad2d_set_position` (`STR` quad_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:quad2d_set_rotation` (`STR` quad_id, `DEC` value) -----> `NONE`
- `fe3d:quad2d_set_size` (`STR` quad_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:quad2d_set_color` (`STR` quad_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:quad2d_set_wireframe_color` (`STR` quad_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:quad2d_set_opacity` (`STR` quad_id, `DEC` value) -----> `NONE`
- `fe3d:quad2d_set_lightness` (`STR` quad_id, `DEC` value) -----> `NONE`
- `fe3d:quad2d_set_texture_repeat` (`STR` quad_id, `INT` value) -----> `NONE`
- `fe3d:quad2d_set_wireframed` (`STR` quad_id, `BOL` value) -----> `NONE`
- `fe3d:quad2d_set_horizontally_flipped` (`STR` quad_id, `BOL` value) -----> `NONE`
- `fe3d:quad2d_set_vertically_flipped` (`STR` quad_id, `BOL` value) -----> `NONE`
- `fe3d:quad2d_set_uv_multiplier` (`STR` quad_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:quad2d_set_uv_offset` (`STR` quad_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:quad2d_set_animation2d_row_index` (`STR` quad_id, `STR` animation_id, `INT` value) -----> `NONE`
- `fe3d:quad2d_set_animation2d_column_index` (`STR` quad_id, `STR` animation_id, `INT` value) -----> `NONE`
- `fe3d:quad2d_set_animation2d_interval_multiplier` (`STR` quad_id, `STR` animation_id, `INT` value) -----> `NONE`
- `fe3d:quad2d_set_animation2d_interval_divider` (`STR` quad_id, `STR` animation_id, `INT` value) -----> `NONE`
- `fe3d:quad2d_set_min_clip_position` (`STR` quad_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:quad2d_set_max_clip_position` (`STR` quad_id, `DEC` x, `DEC` y) -----> `NONE`

## Getters

- `fe3d:quad2d_find_ids` (`STR` quad_id) -----> `LST`
- `fe3d:quad2d_is_visible` (`STR` quad_id) -----> `BOL`
- `fe3d:quad2d_is_horizontally_flipped` (`STR` quad_id) -----> `BOL`
- `fe3d:quad2d_is_vertically_flipped` (`STR` quad_id) -----> `BOL`
- `fe3d:quad2d_is_wireframed` (`STR` quad_id) -----> `BOL`
- `fe3d:quad2d_is_existing` (`STR` quad_id) -----> `BOL`
- `fe3d:quad2d_is_animation2d_started` (`STR` quad_id, `STR` animation_id) -----> `BOL`
- `fe3d:quad2d_is_animation2d_paused` (`STR` quad_id, `STR` animation_id) -----> `BOL`
- `fe3d:quad2d_is_animation2d_autopaused` (`STR` quad_id, `STR` animation_id) -----> `BOL`
- `fe3d:quad2d_has_diffuse_map` (`STR` quad_id) -----> `BOL`
- `fe3d:quad2d_get_position_x` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_position_y` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_rotation` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_size_x` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_size_y` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_color_r` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_color_g` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_color_b` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_wireframe_color_r` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_wireframe_color_g` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_wireframe_color_b` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_opacity` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_lightness` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_texture_repeat` (`STR` quad_id) -----> `INT`
- `fe3d:quad2d_get_ids` () -----> `LST`
- `fe3d:quad2d_get_diffuse_map_path` (`STR` quad_id) -----> `STR`
- `fe3d:quad2d_get_uv_multiplier_x` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_uv_multiplier_y` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_uv_offset_x` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_uv_offset_y` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_animation2d_row_index` (`STR` quad_id, `STR` animation_id) -----> `INT`
- `fe3d:quad2d_get_animation2d_column_index` (`STR` quad_id, `STR` animation_id) -----> `INT`
- `fe3d:quad2d_get_animation2d_play_count` (`STR` quad_id, `STR` animation_id) -----> `INT`
- `fe3d:quad2d_get_animation2d_interval_multiplier` (`STR` quad_id, `STR` animation_id) -----> `INT`
- `fe3d:quad2d_get_animation2d_interval_divider` (`STR` quad_id, `STR` animation_id) -----> `INT`
- `fe3d:quad2d_get_min_clip_position_x` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_min_clip_position_y` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_max_clip_position_x` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_get_max_clip_position_y` (`STR` quad_id) -----> `DEC`
- `fe3d:quad2d_is_hovered` (`STR` quad_id) -----> `BOL`
- `fe3d:quad2d_get_editor_id` (`STR` quad_id) -----> `STR`
