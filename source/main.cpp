#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <stdlib.h>
#include <asndlib.h>

#include "oggplayer.h"
#include "homeless_png.h"
#include "hand_png.h"
#include "soundeffect_ogg.h"

#define White 0xFFFFFFFF

#define click()    (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_A)
#define release()  (WPAD_ButtonsUp(WPAD_CHAN_0) & WPAD_BUTTON_A)
#define hold()     (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A)

int main() {
    GRRLIB_Init();
    WPAD_Init();
    ASND_Init();

    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);

    GRRLIB_texImg *tex_homeless_png = GRRLIB_LoadTexture(homeless_png);
    GRRLIB_texImg *tex_hand_png = GRRLIB_LoadTexture(hand_png);

    int x_homeless = (640 - tex_homeless_png->w) / 2;
    int y_homeless = (480 - tex_homeless_png->h) / 2;

    int x_hand = 0;
    int y_hand = 0;

    int offsetX = 0;
    int offsetY = 0;
    bool dragging = false;

    float scale_factor = 0.5;

    while (1) {
        WPAD_ScanPads();
        ir_t ir;
        WPAD_IR(WPAD_CHAN_0, &ir);

        if (click()) {
            if (ir.x >= x_homeless && ir.x <= x_homeless + tex_homeless_png->w &&
                ir.y >= y_homeless && ir.y <= y_homeless + tex_homeless_png->h) {
                offsetX = ir.x - x_homeless;
                offsetY = ir.y - y_homeless;
                PlayOgg(soundeffect_ogg, soundeffect_ogg_size, 0, 0);
                dragging = true;
            }
        }

        if (dragging) {
            x_homeless = ir.x - offsetX;
            y_homeless = ir.y - offsetY;

            if (release()) {
                dragging = false;
            }
        }

        x_hand = ir.x - (int)(tex_hand_png->w * scale_factor / 2);
        y_hand = ir.y - (int)(tex_hand_png->h * scale_factor / 2);

        GRRLIB_FillScreen(White);
        GRRLIB_DrawImg(x_homeless, y_homeless, tex_homeless_png, 0, 1, 1, White);
        GRRLIB_DrawImg(x_hand, y_hand, tex_hand_png, 0, scale_factor, scale_factor, White);
        GRRLIB_Render();

        if(WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_HOME)
            break;
    }
    StopOgg();
    GRRLIB_FreeTexture(tex_homeless_png);
    GRRLIB_FreeTexture(tex_hand_png);

    GRRLIB_Exit();
    return 0;
}
