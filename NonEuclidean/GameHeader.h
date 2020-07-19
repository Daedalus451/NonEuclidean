#pragma once

#include <cstdint>

class Engine;
class Input;
class Player;

namespace GH
{
// Windows
inline constexpr char TITLE[] = "NonEuclideanDemo";
inline constexpr char CLASS[] = "NED";

// General
inline constexpr float PI = 3.141592653589793f;
inline constexpr int MAX_PORTALS = 16;

// Graphics
inline constexpr bool START_FULLSCREEN = false;
inline constexpr bool HIDE_MOUSE = true;
inline constexpr bool USE_SKY = true;
inline constexpr int SCREEN_WIDTH = 1280;
inline constexpr int SCREEN_HEIGHT = 720;
inline constexpr int SCREEN_X = 50;
inline constexpr int SCREEN_Y = 50;
inline constexpr float FOV = 60.0f;
inline constexpr float NEAR_MIN = 1e-3f;
inline constexpr float NEAR_MAX = 1e-1f;
inline constexpr float FAR_DIST = 100.0f;
inline constexpr int FBO_SIZE = 2048;
inline constexpr int MAX_RECURSION = 4;

// Gameplay
inline constexpr float MOUSE_SENSITIVITY = 0.005f;
inline constexpr float MOUSE_SMOOTH = 0.5f;
inline constexpr float WALK_SPEED = 2.9f;
inline constexpr float WALK_ACCEL = 50.0f;
inline constexpr float BOB_FREQ = 8.0f;
inline constexpr float BOB_OFFS = 0.015f;
inline constexpr float BOB_DAMP = 0.04f;
inline constexpr float BOB_MIN = 0.1f;
inline constexpr float DT = 0.002f;
inline constexpr int MAX_STEPS = 30;
inline constexpr float PLAYER_HEIGHT = 1.5f;
inline constexpr float PLAYER_RADIUS = 0.2f;
inline constexpr float GRAVITY = -9.8f;

// Global variables
extern Engine* ENGINE;
extern Player* PLAYER;
extern const Input* INPUT;
extern int REC_LEVEL;
extern int64_t FRAME;
} // namespace GH
