// Some defines for the elements in the HUD
#define PRG_BANK_HUD 2

#define HUD_POSITION_START 0x0300
#define HUD_HEART_START 0x0361
#define HUD_KEY_START 0x037d
#define HUD_ATTRS_START 0x03f0

#define HUD_TILE_HEART 0xe7
#define HUD_TILE_HEART_EMPTY 0xe9
#define HUD_TILE_KEY 0xe8
#define HUD_TILE_NUMBER 0xf6
#define HUD_TILE_BLANK 0xa0
#define HUD_TILE_BORDER_BL 0x5e
#define HUD_TILE_BORDER_BR 0x5f
#define HUD_TILE_BORDER_HORIZONTAL 0x4f
#define HUD_TILE_BORDER_VERTICAL 0x4e

#define HUD_SPRITE_ZERO_TILE_ID 0x8e

// Draw the HUD
void draw_hud(void);

// Do that, but take a couple frames instead of disabling rendering
void draw_hud_oneshot(void);

// Update the number of hearts, coins, etc in the hud.
void update_hud(void);
