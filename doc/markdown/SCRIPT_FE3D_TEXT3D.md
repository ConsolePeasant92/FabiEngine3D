# Text3D scripting functions

## Setters

- `fe3d:text3d_place` (`STR` new_id, `STR` editor_id, `STR` content, `DEC` position_x, `DEC` position_y, `DEC` position_z) -----> `NONE`
- `fe3d:text3d_delete` (`STR` text_id) -----> `NONE`
- `fe3d:text3d_delete_all` () -----> `NONE`
- `fe3d:text3d_move` (`STR` text_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:text3d_rotate` (`STR` text_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:text3d_scale` (`STR` text_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:text3d_move_to` (`STR` text_id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:text3d_rotate_to` (`STR` text_id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:text3d_scale_to` (`STR` text_id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:text3d_set_content` (`STR` text_id, `STR` value) -----> `NONE`
- `fe3d:text3d_set_visible` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_position` (`STR` text_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:text3d_set_rotation` (`STR` text_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:text3d_set_size` (`STR` text_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:text3d_set_color` (`STR` text_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:text3d_set_wireframe_color` (`STR` text_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:text3d_set_min_clip_position` (`STR` text_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:text3d_set_max_clip_position` (`STR` text_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:text3d_set_opacity` (`STR` text_id, `DEC` value) -----> `NONE`
- `fe3d:text3d_set_lightness` (`STR` text_id, `DEC` value) -----> `NONE`
- `fe3d:text3d_set_aabb_visible` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_shadowed` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_reflected` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_refracted` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_bright` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_wireframed` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_facing_camera_horizontally` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_facing_camera_vertically` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_min_alpha` (`STR` text_id, `DEC` value) -----> `NONE`
- `fe3d:text3d_set_horizontally_flipped` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_vertically_flipped` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text3d_set_rotation_order` (`STR` text_id, `STR` value) -----> `NONE`

## Getters

- `fe3d:text3d_find_ids` (`STR` text_id) -----> `LST`
- `fe3d:text3d_is_visible` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_facing_camera_horizontally` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_facing_camera_vertically` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_shadowed` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_reflected` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_refracted` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_bright` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_wireframed` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_existing` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_horizontally_flipped` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_vertically_flipped` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_is_aabb_visible` (`STR` text_id) -----> `BOL`
- `fe3d:text3d_get_position_x` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_position_y` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_position_z` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_rotation_x` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_rotation_y` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_rotation_z` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_size_x` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_size_y` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_color_r` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_color_g` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_color_b` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_wireframe_color_r` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_wireframe_color_g` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_wireframe_color_b` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_min_clip_position_x` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_min_clip_position_y` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_min_clip_position_z` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_max_clip_position_x` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_max_clip_position_y` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_max_clip_position_z` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_opacity` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_lightness` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_ids` () -----> `LST`
- `fe3d:text3d_get_font_map_path` (`STR` text_id) -----> `STR`
- `fe3d:text3d_get_content` (`STR` text_id) -----> `STR`
- `fe3d:text3d_get_min_alpha` (`STR` text_id) -----> `DEC`
- `fe3d:text3d_get_rotation_order` (`STR` text_id) -----> `STR`
- `fe3d:text3d_get_editor_id` (`STR` text3d_id) -----> `STR`
