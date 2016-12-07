#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>

#include <functional>
#include <memory>

#include "starlight/InputManager.h"
#include "starlight/datatypes/Vector2.h"

#include "starlight/ThemeManager.h"
#include "starlight/gfx/ThemeRef.h"

//#include "starlight/ui/UIElement.h"

#include "starlight/gfx/DrawableTest.h"
#include "starlight/gfx/DrawContextTouchscreen.h"
#include "starlight/GFXManager.h"

#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)

using starlight::Vector2;
using starlight::InputManager;

/*Handle *signalEvent = NULL;
Handle *resumeEvent = NULL;

Handle *nssHandle = NULL;//*/

//aptMessageCb callback = {NULL, APPID_HOMEMENU, "boop", sizeof("boop")};

/*void __appInit() {
  srvInit();
  hidInit();

  fsInit();
  sdmcInit();

  gfxInitDefault();
  consoleInit(GFX_TOP, NULL);
}//*/

int main()
{
    /*printf("does this draw\n");
    APT_Initialize(APPID_HOMEMENU, aptMakeAppletAttr(APTPOS_SYS, true, true), signalEvent, resumeEvent);
    while (aptMainLoop()) {
        hidScanInput();
        u32 k = hidKeysDown();
        if (k & KEY_A) printf("this is a test\n");
        if (k & KEY_START) return 0;
        
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }*/
    
    
    // Set the random seed based on the time
    srand(time(NULL));
    
    romfsInit();
    
    sf2d_init();
    //sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
    sf2d_set_clear_color(RGBA8(0x00, 0x00, 0x00, 0xFF));
    sf2d_set_3D(1);
    sf2d_set_vblank_wait(1);
    
    sftd_init();
    sftd_font *font = sftd_load_font_file("romfs:/Arcon-Regular.otf");
    
    float offset3d = 0.0f;
    float rad = 0.0f;
    u16 touch_x = 320/2;
    u16 touch_y = 240/2;
    touchPosition touch;
    circlePosition circle;
    u32 held;
    
    Vector2 circpos (16.0f, 16.0f);
    
    char sbuf[100];
    
    // test drawables
    std::shared_ptr<starlight::gfx::DrawContext> con = std::make_shared<starlight::gfx::DrawContextTouchscreen>();
    //std::shared_ptr<starlight::gfx::Drawable> drw = std::make_shared<starlight::gfx::DrawableTest>();
    
    while (aptMainLoop()) {

        //hidScanInput();
        //hidCircleRead(&circle);
        InputManager::Update();
        held = hidKeysHeld();
        
        Vector2 cpad = InputManager::CirclePad();
        
        if (held & KEY_START) {
            break;
        } else if (held & KEY_TOUCH) {
            hidTouchRead(&touch);
            touch_x = touch.px;
            touch_y = touch.py;
        } else if (held & (KEY_L | KEY_R)) {
            sf2d_set_clear_color(RGBA8(rand()%255, rand()%255, rand()%255, 255));
        }
        
        //if (InputManager::Held(KEY_TOUCH))
        circpos = circpos + InputManager::TouchDelta();
        
        offset3d = CONFIG_3D_SLIDERSTATE * 30.0f;
        
        //sf2d_start_frame(GFX_TOP, GFX_LEFT); sf2d_end_frame();
        sf2d_start_frame(GFX_TOP, GFX_LEFT);
            sf2d_draw_fill_circle(offset3d + 60, 100, 35, RGBA8(0x00, 0xFF, 0x00, 0xFF));
            sf2d_draw_fill_circle(circpos.x + cpad.x * 20.0f, circpos.y + cpad.y * 20.0f, 55, RGBA8(0xFF, 0xFF, 0x00, (int)(0xFF * (0.75f * cpad.Length() + 0.25f))));
        
            sf2d_draw_rectangle_rotate(offset3d + 260, 20, 40, 40, RGBA8(0xFF, 0xFF, 0x00, 0xFF), -2.0f*rad);
            sf2d_draw_rectangle(offset3d + 20, 60, 40, 40, RGBA8(0xFF, 0x00, 0x00, 0xFF));
            sf2d_draw_rectangle(offset3d + 5, 5, 30, 30, RGBA8(0x00, 0xFF, 0xFF, 0xFF));
            //sf2d_draw_texture_rotate(tex1, offset3d + 400/2 + circle.dx, 240/2 - circle.dy, rad);
        sf2d_end_frame();
        
        sf2d_start_frame(GFX_TOP, GFX_RIGHT);
            
            sftd_draw_text(font, 3, 1, RGBA8(255,255,255,255), 16, "THEY'RE MOULDY YOU PILLOCK\nWelcome to the secret text~");
            
            /*sf2d_draw_fill_circle(60, 100, 35, RGBA8(0x00, 0xFF, 0x00, 0xFF));
            sf2d_draw_fill_circle(180, 120, 55, RGBA8(0xFF, 0xFF, 0x00, 0xFF));
        
            sf2d_draw_rectangle_rotate(260, 20, 40, 40, RGBA8(0xFF, 0xFF, 0x00, 0xFF), -2.0f*rad);
            sf2d_draw_rectangle(20, 60, 40, 40, RGBA8(0xFF, 0x00, 0x00, 0xFF));
            sf2d_draw_rectangle(5, 5, 30, 30, RGBA8(0x00, 0xFF, 0xFF, 0xFF));*/
            //sf2d_draw_texture_rotate(tex1, 400/2 + circle.dx, 240/2 - circle.dy, rad);
        sf2d_end_frame();
        
        /*sf2d_start_frame(GFX_BOTTOM, GFX_LEFT); {
            
            const int tileSize = 48;
            const int tileSpace = 3;
            for (int iy = 0; iy < 4; iy++) {
                for (int ix = 0; ix < 5; ix++) {
                    sf2d_draw_rectangle(34 + ix * (tileSize+tileSpace), 3 + iy * (tileSize+tileSpace), tileSize, tileSize, RGBA8(0x7F, 0xBF, 0xFF, 0xFF));
                }
            }
            
            Vector2 test (circle.dx, circle.dy);
            test = test * .5f;
            
            Vector2 tdrag = InputManager::TouchDelta();
            
            sprintf(sbuf, "Circle pad: %f, %f\nTouch: %f, %f\nVec: %f", cpad.x, cpad.y, tdrag.x, tdrag.y, test.x);
            sftd_draw_text(font, 3, 3, RGBA8(0xff, 0xff, 0xff, 0xff), 16, sbuf);
            
            
        } sf2d_end_frame();*/
        
        using starlight::GFXManager;
        GFXManager::PushContext(con.get());
        static auto drw = starlight::ThemeManager::GetAsset("whatever");
        drw->Draw(Vector2(48, 32));
        drw->Draw(Vector2(122, 33));
        GFXManager::PopContext();
        
        rad += 0.2f;
        
        sf2d_swapbuffers();
    }
    
    sftd_fini();
    sf2d_fini();
    return 0;
}
