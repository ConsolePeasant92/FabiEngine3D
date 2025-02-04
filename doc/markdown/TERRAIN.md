# Terrain

## 1. General

- The terrain is a 3D object in 3D space.
- The mesh of a terrain is generated using a height map.

## 2. Assets

- Height map
- Blend map
- Diffuse map
- Normal map

## 3. Properties

- **ID**: the unique identifier of the terrain
  - Type: `string`
  - Constraints: cannot be empty or contain spaces/capitals/specials
- **Height Map Path**: the path of the height map file
  - Type: `string`
  - Constraints: cannot be changed
- **Diffuse Map Path**: the path of the diffuse map file
  - Type: `string`
  - Constraints: none
- **Normal Map Path**: the path of the normal map file
  - Type: `string`
  - Constraints: none
- **Blend Map Path**: the path of the blend map file
  - Type: `string`
  - Constraints: none
- **Red Diffuse Map Path**: the path of the red diffuse map file
  - Type: `string`
  - Constraints: none
- **Green Diffuse Map Path**: the path of the green diffuse map file
  - Type: `string`
  - Constraints: none
- **Blue Diffuse Map Path**: the path of the blue diffuse map file
  - Type: `string`
  - Constraints: none
- **Red Normal Map Path**: the path of the red normal map file
  - Type: `string`
  - Constraints: none
- **Green Normal Map Path**: the path of the green normal map file
  - Type: `string`
  - Constraints: none
- **Blue Normal Map Path**: the path of the blue normal map file
  - Type: `string`
  - Constraints: none
- **Color**: the RGB color multiplier of the mesh
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Wireframe Color**: the RGB color multiplier of the wireframe
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Min Clip Position**: the minimum position from which the mesh is visible
  - Type: `decimal3`
  - Constraints: none
- **Max Clip Position**: the maximum position to which the mesh is visible
  - Type: `decimal3`
  - Constraints: none
- **Max Height**: the maximum height of the mesh
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Size**: the size of the mesh
  - Type: `decimal`
  - Constraints: between `0.0` and `1024.0`
- **Lightness**: the lightness multiplier of the mesh
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Specular Shininess**: the shininess of the specular lighting
  - Type: `decimal`
  - Constraints: at least `1.0`
- **Specular Intensity**: the intensity of the specular lighting
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Texture Repeat**: the amount of times the textures are repeated
  - Type: `integer`
  - Constraints: at least `1`
- **Red Texture Repeat**: the amount of times the textures of the red blend map channel are repeated
  - Type: `integer`
  - Constraints: at least `1`
- **Green Texture Repeat**: the amount of times the textures of the green blend map channel are repeated
  - Type: `integer`
  - Constraints: at least `1`
- **Blue Texture Repeat**: the amount of times the textures of the blue blend map channel are repeated
  - Type: `integer`
  - Constraints: at least `1`
- **Specular**: specular lighting is rendered on the mesh
  - Type: `boolean`
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Type: `boolean`
  - Constraints: none
- **Shadowed**: the mesh is captured for shadows
  - Type: `boolean`
  - Constraints: none
