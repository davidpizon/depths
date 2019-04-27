#include "source/menus/game_over.h"
#include "source/graphics/palettes.h"
#include "source/configuration/system_constants.h"
#include "source/globals.h"
#include "source/neslib_asm/neslib.h"
#include "source/configuration/game_states.h"
#include "source/menus/text_helpers.h"
#include "source/menus/input_helpers.h"

CODE_BANK(PRG_BANK_GAME_OVER);

const unsigned char game_over[394]={
0x02,0x00,0x02,0x40,0xe0,0xf6,0x00,0x24,0x45,0x50,0x54,0x48,0x53,0x00,0xf6,0x02,
0x12,0xe1,0x00,0x00,0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,0xe4,0x00,0x29,0x00,0x46,
0x4f,0x55,0x4e,0x44,0x00,0x4d,0x59,0x53,0x45,0x4c,0x46,0x00,0x53,0x54,0x41,0x52,
0x54,0x49,0x4e,0x47,0x00,0x54,0x4f,0x00,0xe4,0x00,0x00,0xe4,0x00,0x44,0x52,0x49,
0x46,0x54,0x00,0x54,0x4f,0x00,0x54,0x48,0x45,0x00,0x42,0x4f,0x54,0x54,0x4f,0x4d,
0x00,0x4f,0x46,0x00,0x54,0x48,0x45,0x00,0xe4,0x00,0x00,0xe4,0x00,0x4f,0x43,0x45,
0x41,0x4e,0x0e,0x02,0x02,0x00,0x02,0x12,0xe4,0x00,0x00,0xe4,0x00,0x02,0x1b,0xe4,
0x00,0x00,0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,0xe4,0x00,0x26,0x4f,0x52,0x00,0x53,
0x4f,0x4d,0x45,0x00,0x52,0x45,0x41,0x53,0x4f,0x4e,0x00,0x29,0x00,0x46,0x4f,0x55,
0x4e,0x44,0x00,0x02,0x03,0xe4,0x00,0x00,0xe4,0x00,0x4d,0x59,0x53,0x45,0x4c,0x46,
0x00,0x49,0x4d,0x41,0x47,0x49,0x4e,0x49,0x4e,0x47,0x00,0x02,0x0a,0xe4,0x00,0x00,
0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,0xe4,0x00,
0x02,0x1b,0xe4,0x00,0x00,0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,0xe4,0x00,0x02,0x1b,
0xe4,0x00,0x00,0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,0xe4,0x00,0x34,0x48,0x45,0x00,
0x45,0x41,0x53,0x45,0x00,0x4f,0x46,0x00,0x4a,0x55,0x53,0x54,0x00,0x44,0x52,0x49,
0x46,0x54,0x49,0x4e,0x47,0x00,0x00,0xe4,0x00,0x00,0xe4,0x00,0x41,0x57,0x41,0x59,
0x00,0x41,0x4c,0x4d,0x4f,0x53,0x54,0x00,0x46,0x45,0x4c,0x54,0x00,0x4c,0x49,0x4b,
0x45,0x00,0x02,0x05,0xe4,0x00,0x00,0xe4,0x00,0x46,0x41,0x4e,0x54,0x41,0x53,0x59,
0x0e,0x02,0x02,0x00,0x02,0x10,0xe4,0x00,0x00,0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,
0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,0xe4,0x00,
0x22,0x55,0x54,0x00,0x4e,0x4f,0x0c,0x00,0x29,0x00,0x43,0x41,0x4e,0x07,0x54,0x00,
0x47,0x49,0x56,0x45,0x00,0x55,0x50,0x00,0x02,0x03,0xe4,0x00,0x00,0xe4,0x00,0x54,
0x48,0x49,0x53,0x00,0x45,0x41,0x53,0x49,0x4c,0x59,0x01,0x00,0x02,0x0e,0xe4,0x00,
0x00,0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,0xe4,0x00,0x02,0x1b,0xe4,0x00,0x00,0xf0,
0xf6,0x02,0x1b,0xf1,0x00,0x02,0x7f,0x00,0x02,0x00
};

#define FATE_COUNT 8
const unsigned char* unfortunateFates[] = {
//  "                         "
    "passing away in an       ",
    "unexpected accident      ",

    "passing away quietly in  ",
    "my sleep.",

    "passing away from a      ",
    "terminal disease.        ",

    "passing away in the shock",
    "of an earthquake.        ",

    "being swept away in a    ",
    "freak hurricane.         ",

    "Just... passing away,    ",
    "for no obvious reason.",

    "Passing away from a heart",
    "attack.",

    "A plane's engines        ",
    "failing at 30, 000 feet. "

};

void draw_game_over_screen(void) {
    set_vram_update(NULL);
    ppu_off();

    // We reuse the title palette here, though we have the option of making our own if needed.
    pal_bg(titlePalette);
	pal_spr(titlePalette);
    scroll(0, 0);

	set_chr_bank_0(CHR_BANK_MENU);
    set_chr_bank_1(CHR_BANK_MENU);

    vram_adr(NAMETABLE_A);
    vram_unrle(game_over);

    tempChar1 = (rand8() % FATE_COUNT)<<1;
    vram_adr(0x2163);


    for (i = 0; i != 25; ++i) {
        tempChar3 = unfortunateFates[tempChar1][i];
        if (tempChar3 == NULL) {
            break;
        }
        vram_put(tempChar3 - 0x20);
    }

    vram_adr(0x2183);
    ++tempChar1;

    for (i = 0; i != 25; ++i) {
        tempChar3 = unfortunateFates[tempChar1][i];
        if (tempChar3 == NULL) {
            break;
        }
        vram_put(tempChar3 - 0x20);
    }



    // We purposely leave sprites off, so they do not clutter the view. 
    // This means all menu drawing must be done with background tiles - if you want to use sprites (eg for a menu item),
    // you will have to hide all sprites, then put them back after. 
    ppu_on_bg();

}