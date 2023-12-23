#include <grrlib.h>
#include <cstdio>

#include "test_jpg.h"

#define Purple  0x800080FF

int main() {
    GRRLIB_Init();

    GRRLIB_texImg *tex_test_jpg = GRRLIB_LoadTexture(test_jpg);

    while (1) {
        GRRLIB_FillScreen(Purple);

        //calculaye where to draw the image
        int imageWidth = tex_test_jpg->w;
        int imageHeight = tex_test_jpg->h;
        int x = (640 - imageWidth) / 2;
        int y = (480 - imageHeight) / 2; 

        GRRLIB_DrawImg(x, y, tex_test_jpg, 0, 1, 1, Purple);

        GRRLIB_Render();
    }

    GRRLIB_FreeTexture(tex_test_jpg);

    GRRLIB_Exit();
    return 0;
}
