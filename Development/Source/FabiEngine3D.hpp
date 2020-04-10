#pragma once

#include <GLM/glm.hpp>
#include <string>
#include <vector>
#include <memory>

using std::vector;
using std::string;
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::ivec2;
using glm::ivec3;
using glm::ivec4;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::make_shared;

#include "InputTypes.hpp"
#include "Logger.hpp"

class CoreEngine;

class FabiEngine3D
{
	friend class CoreEngine;
public:
	FabiEngine3D();
	virtual ~FabiEngine3D();

	// Engine interface
	void engine_start();
	void engine_stop();

	// Camera interface
	void  camera_load(float fov, float nearZ, float farZ, vec3 startPos, float yaw = 0.0f, float pitch = 0.0f);
	void  camera_enableFirstPersonView(float mouseSensitivity);
	void  camera_disableFirstPersonView();
	void  camera_enableFreeMovement();
	void  camera_disableFreeMovement();
	void  camera_translateFollowX(float speed);
	void  camera_translateFollowZY(float speed);
	void  camera_translateFollowZ(float speed);
	void  camera_translate(vec3 translation);
	void  camera_setPosition(vec3 pos);
	void  camera_invertYaw();
	void  camera_invertPitch();
	void  camera_setFOV(float fov);
	void  camera_setSensitivity(float speed);
	void  camera_setYaw(float val);
	void  camera_setPitch(float val);
	float camera_getYaw();
	float camera_getPitch();
	float camera_getMouseOffset();
	vec3  camera_getPos();
	vec3  camera_getFront();

	// Sky entity interface
	void skyEntity_add
	(
		const string& ID, const string& dayDirectory, const string& nightDirectory, float rotationSpeed
	);
	void skyEntity_delete(const string& ID);
	void skyEntity_setAmbientLighting(const string& ID, float nightAmbStrength, float dayAmbStrength);
	void skyEntity_setDirectionalLighting(const string& ID, float nightDirStrength, float dayDirStrength);
	bool skyEntity_isExisting(const string& ID);
	void skyEntity_select(const string& ID);
	void skyEntity_setDayTime(const string& ID);
	void skyEntity_setNightTime(const string& ID);
	void skyEntity_fadeDayTime(const string& ID);
	void skyEntity_fadeNightTime(const string& ID);
	bool skyEntity_isDayTime(const string& ID);
	bool skyEntity_isNightTime(const string& ID);
	string skyEntity_getSelectedID();

	// Terrain entity interface
	void terrainEntity_add(const string& ID, const string& heightmapName, const string& textureName, vec3 pos, float size, float maxHeight, float uvRepeat);
	void terrainEntity_delete(const string& ID);
	void terrainEntity_select(const string& ID);
	bool terrainEntity_isExisting(const string& ID);
	bool terrainEntity_isInside(float x, float z);
	vec3 terrainEntity_getMousePoint();
	float terrainEntity_getPixelHeight(float x, float z);
	string terrainEntity_getSelectedID();
	void terrainEntity_addBlending
	(
		const string& ID, const string blendmapName, const string blendmapNameR,
		const string blendmapNameG, const string blendmapNameB,
		float blendRepeatR, float blendRepeatG, float blendRepeatB
	);

	// Water entity interface
	void waterEntity_add
	(
		const string& ID, const string& assetName, vec3 pos, float size,
		float tileRepeat, float speed, bool waving,
		bool rippling, vec3 color, float shininess
	);
	void waterEntity_delete(const string& ID);
	bool waterEntity_isExisting(const string& ID);
	void waterEntity_select(const string& ID);
	void waterEntity_enableWaving(const string& ID);
	void waterEntity_disableWaving(const string& ID);
	void waterEntity_enableRippling(const string& ID);
	void waterEntity_disableRippling(const string& ID);
	void waterEntity_setColor(const string& ID, vec3 color);
	void waterEntity_setShininess(const string& ID, float shininess);
	void waterEntity_setTransparency(const string& ID, float transparency);
	string waterEntity_getSelectedID();

	// Game entity interface
	void gameEntity_add
	(
		const string& ID, const string& modelName,
		vec3 position, vec3 rotation, vec3 size,
		bool transparent, bool faceCulled, bool lightMapped, bool reflective, bool specular, bool visible = true
	);
	void gameEntity_addInstanced
	(
		const string& ID, const string& modelName,
		const vector<vec3>& positions, vec3 rotation, vec3 size,
		bool transparent, bool faceCulled, bool lightMapped, bool reflective, bool specular
	);
	void gameEntity_deleteAll();
	void gameEntity_delete(const string& ID);
	void gameEntity_deleteGroup(const string& ID);
	void gameEntity_hideAll();
	void gameEntity_showAll();
	void gameEntity_hide(const string& ID);
	void gameEntity_show(const string& ID);
	bool gameEntity_isExisting(const string& ID);
	bool gameEntity_isVisible(const string& ID);
	void gameEntity_move(const string& ID, vec3 factor);
	void gameEntity_rotate(const string& ID, vec3 factor);
	void gameEntity_scale(const string& ID, vec3 factor);
	void gameEntity_setPosition(const string& ID, vec3 position);
	void gameEntity_setRotation(const string& ID, vec3 rotation);
	void gameEntity_setSize(const string& ID, vec3 size);
	vec3 gameEntity_getPosition(const string& ID);
	vec3 gameEntity_getRotation(const string& ID);
	vec3 gameEntity_getSize(const string& ID);
	void gameEntity_enable(const string& ID);
	void gameEntity_disable(const string& ID);
	void gameEntity_setSceneReflective(const string& ID, bool enabled);
	void gameEntity_setAlpha(const string& ID, float alpha);
	void gameEntity_setShadowed(const string& ID, bool shadowed);
	void gameEntity_setColor(const string& ID, vec3 color);
	void gameEntity_setMaxY(const string& ID, float y);
	void gameEntity_setUvRepeat(const string& ID, float repeat);
	float gameEntity_getMaxY(const string& ID);
	vector<string> gameEntity_getGroupIDs(const string& ID);

	// Billboard entity interface
	void billBoardEntity_add
	(
		const string& ID, const string& text,
		const string& fontName, vec3 color,
		vec3 T, vec3 R, vec3 S, bool facingCameraX, bool facingCameraY, bool visible = true
	);
	void billBoardEntity_add
	(
		const string& ID, const string& textureName,
		vec3 T, vec3 R, vec3 S,
		bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering, bool visible = true
	);
	void billboardEntity_deleteAll();
	void billboardEntity_delete(const string& ID);
	void billboardEntity_hideAll();
	void billboardEntity_showAll();
	void billboardEntity_hide(const string& ID);
	void billboardEntity_show(const string& ID);
	bool billboardEntity_isExisting(const string& ID);
	void billboardEntity_move(const string& ID, vec3 factor);
	void billboardEntity_rotate(const string& ID, vec3 factor);
	void billboardEntity_scale(const string& ID, vec3 factor);
	void billboardEntity_setPosition(const string& ID, vec3 position);
	void billboardEntity_setRotation(const string& ID, vec3 rotation);
	void billboardEntity_setSize(const string& ID, vec3 size);
	vec3 billboardEntity_getPosition(const string& ID);
	vec3 billboardEntity_getRotation(const string& ID);
	vec3 billboardEntity_getSize(const string& ID);
	void billboardEntity_enable(const string& ID);
	void billboardEntity_disable(const string& ID);
	void billBoardEntity_playSpriteAnimation(const string& ID, int rows, int columns, float maxDelta, int repeats);
	void billBoardEntity_changeText(const string& ID, const string& text, const string& fontName, vec3 color);
	bool billboardEntity_isFinished(const string& ID);

	// AABB entity interface
	void aabbEntity_deleteAll();
	void aabbEntity_add(const string& ID, vec3 T, vec3 S, bool responsive);
	void aabbEntity_bindToGameEntity(const string& parentID, vec3 S, bool responsive);
	void aabbEntity_bindToGameEntityGroup(const string& parentID, vec3 S, bool responsive);
	void aabbEntity_delete(const string& ID);
	void aabbEntity_setResponsiveness(const string& ID, bool responsive);
	void aabbEntity_setGroupResponsiveness(const string& ID, bool responsive);
	void aabbEntity_setPosition(const string& ID, vec3 position);
	void aabbEntity_setSize(const string& ID, vec3 size);
	vec3 aabbEntity_getPosition(const string& ID);
	vec3 aabbEntity_getSize(const string& ID);
	bool aabbEntity_isExisting(const string& ID);

	// Global collision interface
	void collision_enableCameraResponse();
	void collision_disableCameraResponse();
	void collision_enableCameraTerrainResponse(float cameraHeight, float cameraSpeed);
	void collision_disableCameraTerrainResponse();
	void collision_enableFrameRendering();
	void collision_disableFrameRendering();
	bool collision_checkCursorInEntity(const string& ID);
	bool collision_checkAnyWithCamera();
	bool collision_checkEntityCamera(const string& ID);
	bool collision_isCameraUnderGround();
	bool collision_isCameraAboveGround();
	string collision_checkEntityOthers(const string ID);
	string collision_checkEntityGroupCamera(const string& ID);
	string collision_checkCursorInEntityGroup(const string& ID, const string exception = "");
	ivec3 collision_checkEntityCameraDir(const string& ID);
	ivec3 collision_checkEntityGroupCameraDir(const string& ID);

	// Light entity interface
	void lightEntity_deleteAll();
	void lightEntity_add(const string& ID, vec3 position, vec3 color, float strength);
	void lightEntity_delete(const string& ID);
	void lightEntity_hide(const string& ID);
	void lightEntity_show(const string& ID);
	bool lightEntity_isExisting(const string& ID);
	void lightEntity_setPosition(const string& ID, vec3 position);
	void lightEntity_setColor(const string& ID, vec3 color);
	void lightEntity_setStrength(const string& ID, float strength);

	// Gui entity interface
	void guiEntity_deleteAll();
	void guiEntity_hideAll();
	void guiEntity_showAll();
	void guiEntity_add(const string& ID, const string& assetName, vec2 translation, float rotation, vec2 scaling, bool centered, bool visible = true);
	void guiEntity_add(const string& ID, vec3 color, vec2 translation, float rotation, vec2 scaling, bool centered, bool visible = true);
	void guiEntity_hide(const string& ID);
	void guiEntity_show(const string& ID);
	void guiEntity_delete(const string& ID);
	void guiEntity_changeTexture(const string& ID, const string& assetName);
	bool guiEntity_isExisting(const string& ID);
	void guiEntity_setPosition(const string& ID, vec2 position);
	void guiEntity_setRotation(const string& ID, float rotation);
	void guiEntity_setSize(const string& ID, vec2 size);
	void guiEntity_move(const string& ID, vec2 position);
	void guiEntity_rotate(const string& ID, float rotation);
	void guiEntity_scale(const string& ID, vec2 size);
	void guiEntity_setColor(const string& ID, vec3 color);
	vec2 guiEntity_getPosition(const string& ID);
	float guiEntity_getRotation(const string& ID);
	vec2 guiEntity_getSize(const string& ID);
	bool guiEntity_isVisible(const string& ID);

	// Text interface
	void textEntity_deleteAll();
	void textEntity_hideAll();
	void textEntity_showAll();
	void textEntity_add
	(
		const string& ID, const string& text,
		const string& fontName, vec3 color,
		vec2 position, float rotation, vec2 size, bool centered
	);
	void textEntity_delete(const string& ID);
	bool textEntity_isExisting(const string& ID);
	void textEntity_setTextContent(const string& ID, const string& textContent, float charWidth);
	void textEntity_setColor(const string& ID, vec3 color);
	void textEntity_hide(const string& ID);
	void textEntity_show(const string& ID);
	void textEntity_setPosition(const string& ID, vec2 position);
	void textEntity_setRotation(const string& ID, float rotation);
	void textEntity_setSize(const string& ID, vec2 size);
	void textEntity_move(const string& ID, vec2 position);
	void textEntity_rotate(const string& ID, float rotation);
	void textEntity_scale(const string& ID, vec2 size);
	vec2 textEntity_getPosition(const string& ID);
	float textEntity_getRotation(const string& ID);
	vec2 textEntity_getSize(const string& ID);
	string textEntity_getTextContent(const string& ID);

	// Graphics interface
	void gfx_addAmbientLighting(float strength = 0.0f);
	void gfx_addDirectionalLighting(vec3 position, float strength = 0.0f);
	void gfx_addSpecularLighting(float shininess);
	void gfx_addPointLighting();
	void gfx_addFog(float minDistance);
	void gfx_addSkyReflections(float factor);
	void gfx_addSceneReflections(float height, float factor);
	void gfx_addLightMapping();
	void gfx_addMSAA();
	void gfx_addShadows(vec3 eye, vec3 center, float size, float reach);
	void gfx_addBloom(float intensity, float brightnessTreshold, int blurSize);
	void gfx_addWaterEffects();
	void gfx_addSkyHDR();
	void gfx_addDOF(float minDistance);
	void gfx_addMotionBlur();
	void gfx_removeAmbientLighting();
	void gfx_removeDirectionalLighting();
	void gfx_removeSpecularLighting();
	void gfx_removePointLighting();
	void gfx_removeFog();
	void gfx_removeSkyReflections();
	void gfx_removeSceneReflections();
	void gfx_removeLightMapping();
	void gfx_removeMSAA();
	void gfx_removeShadows();
	void gfx_removeBloom();
	void gfx_removeWaterEffects();
	void gfx_removeSkyHDR();
	void gfx_removeDOF();
	void gfx_removeMotionBlur();
	void gfx_setSkyBrightness(float brightness);
	float gfx_getSkyBrightness();

	// Input interface
	bool input_getKeyDown(Input keyName);
	bool input_getKeyPressed(Input keyName);
	bool input_getKeyToggled(Input keyName);
	bool input_getMouseDown(Input mouseButton);
	bool input_getMousePressed(Input mouseButton);
	bool input_getMouseToggled(Input mouseButton);
	int  input_getMouseWheelX();
	int  input_getMouseWheelY();

	// Audio interface
	void audioEntity_setSoundEnabled(bool val);
	void audioEntity_setMusicEnabled(bool val);
	void audioEntity_deleteAllSounds();
	void audioEntity_deleteAllMusic();
	void audioEntity_stopAllSounds();
	void audioEntity_stopAllMusic();
	void audioEntity_addMusic(const std::string& fileName);
	void audioEntity_deleteMusic();
	void audioEntity_setMusicVolume(int volume);
	void audioEntity_addGlobal(const std::string& ID, const std::string& fileName);
	void audioEntity_addPoint(const std::string& ID, const std::string& fileName, vec3 position, float maxDistance);
	void audioEntity_delete(const std::string& ID);
	void audioEntity_play(const std::string& ID, int loops, int initialVolume, bool noRestart = false, int fadeMillis = 0);
	void audioEntity_pause(const std::string& ID);
	void audioEntity_resume(const std::string& ID);
	void audioEntity_stop(const std::string& ID, int fadeMillis = 0);
	void audioEntity_setVolume(const std::string& ID, int volume);
	void audioEntity_changePoint(const std::string& ID, vec3 position);
	bool audioEntity_isPlaying(const std::string& ID);
	int  audioEntity_getVolume(const std::string& ID);
	int  audioEntity_getUsedChannelCount();

	// Logger interface
	template<typename T, typename...Rest> inline void logger_throwInfo(T first, Rest...rest)
	{
		Logger::getInst().throwInfo(first, rest...);
	}

	template<typename T, typename...Rest> inline void logger_throwError(T first, Rest...rest)
	{
		Logger::getInst().throwError(first, rest...);
	}

	template<typename T, typename...Rest> inline void logger_throwDebug(T first, Rest...rest)
	{
		Logger::getInst().throwDebug(first, rest...);
	}

	template<typename T, typename...Rest> inline void logger_throwWarning(T first, Rest...rest)
	{
		Logger::getInst().throwWarning(first, rest...);
	}

	// Miscellaneous interface
	int misc_getUniqueInt();
	int misc_getWindowWidth();
	int misc_getWindowHeight();
	int misc_getRandomInt(int min, int max);
	int misc_getMsTimeSinceEpoch();
	float misc_getRandomFloat(float min, float max);
	float misc_getAspectRatio();
	void misc_showCursor();
	void misc_hideCursor();
	void misc_enableWireframeRendering();
	void misc_disableWireframeRendering();
	void misc_enableDebugRendering();
	void misc_disableDebugRendering();
	void misc_setMousePos(ivec2 pos);
	void misc_preLoadGameEntity(const std::string& assetName, bool lightMapped, bool reflective);
	void misc_showPerformanceProfiling();
	void misc_hidePerformanceProfiling();
	void misc_showAudioDebugging();
	void misc_hideAudioDebugging();
	string misc_vec2str(vec2 vec);
	string misc_vec2str(vec3 vec);
	string misc_vec2str(vec4 vec);
	ivec2 misc_getMousePos();
	vec2 misc_convertToNDC(vec2 pos);
	vec2 misc_convertFromNDC(vec2 pos);
	ivec2 misc_convertToScreenCoords(vec2 pos);
	vec2 misc_convertFromScreenCoords(ivec2 pos);

	// World interface
	bool world_check(const string& worldName);
	void world_load(const string& worldName);
	void world_export(const string& worldName);

protected:
	// Virtual interface
	virtual void FE3D_CONTROLLER_INIT() = 0;
	virtual void FE3D_CONTROLLER_UPDATE(float delta) = 0;
	virtual void FE3D_CONTROLLER_DESTROY() = 0;

private:
	CoreEngine* _core = nullptr;
};