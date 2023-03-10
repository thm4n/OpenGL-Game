#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define GLFW_DLL

#define WINDOW_CLEAR_COLOR 0.2f, 0.3f, 1.0f, 1.0f

#define WINDOW_BASE_WIDTH 720.0f
#define WINDOW_BASE_HEIGHT 720.0f
#define WH_RATIO ((double)WINDOW_BASE_WIDTH / (double)WINDOW_BASE_HEIGHT)

#define PLAYER_BASE_SPEED     0.05f
#define GRAVITY               0.00f

#define BLOCK_SCALE           1.00f
#define CURSOR_MOVEMENT_SCALE 0.50f
#define MAP_SIZE              4
#define CHUNK_SIZE            4
#define Y_MAX                 8
#define TEXTURE_COUNT         1

#define FPS_CAP               60.0f
#define TICK_RATE             3

#define PLUS_ARM_LEN 12
#define PLUS_ARM_WID 01

#define UNUSED(x) [&x]{}()
#define arrLen(x) (int)(sizeof(x)/sizeof(x[0]))
#define printmat4(x) [&x]{for(int i = 0; i < 4; i++) printf("|%.2f, %.2f, %.2f, %.2f|\n", x[i][0], x[i][1], x[i][2], x[i][3]);}()

namespace game {
	enum struct block_t {
		_void = 0,
		_dirt = 1
	};

	enum struct obj_t {
		_void = 0,
		_player = 1,
	};
}

#endif
