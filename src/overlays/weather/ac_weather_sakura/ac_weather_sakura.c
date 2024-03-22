#include "ac_weather_sakura.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "macros.h"

extern Gfx ef_hanabira01_00_setmode[];
extern Gfx ef_hanabira01_00_modelT[];

void aWeatherSakura_make(Actor*, Game_Play*);
void aWeatherSakura_ct(WeatherPrv* priv, Game_Play* play);
void aWeatherSakura_move(WeatherPrv*, Game_Play*);
void aWeatherSakura_set(Game_Play*);
void aWeatherSakura_draw(WeatherPrv*, Game_Play*);

WeatherProfile iam_weather_sakura = {
    aWeatherSakura_make,
    aWeatherSakura_ct,
    aWeatherSakura_move,
    aWeatherSakura_set,
    aWeatherSakura_draw,
};

s32 aWeatherSakura_DecideMakeSakuraCount(Actor* thisx, Game_Play* play){
    Weather* this = (Weather*)thisx;
    s32 cur = this->currentLevel;

    if(cur == 1){
        if(!(play->state.frameCounter & 3)){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        if((play->state.frameCounter & 1)){
            return 1;
        }
        else{
            return 0;
        }
    } 
} 

void aWeatherSakura_make(Actor* thisx, Game_Play* play){
    Weather* this = (Weather*)thisx;
    xyz_t pos = this->pos;
    f32 y = pos.y + 230.0f;
    s32 count  = common_data.clip.weatherClip->getPrvNum(thisx);
    xyz_t base = {0.0f, 0.0f, 0.0f};
    UNUSED s32 pad;
    WeatherPrv* priv;  
    f32 x;
    f32 z;
    xyz_t modPos;

    if(aWeatherSakura_DecideMakeSakuraCount(thisx, play) != 0){
        base.y = -1.6f + (RANDOM_F(-0.19999993f));
        if(count != -1){
            x = -100.0f + (RANDOM_F(200.0f));
            z = -200.0f + (RANDOM_F(380.0f));
        
            modPos = pos;

            modPos.x += x;
            modPos.z += z;
            modPos.y = y;
            
            priv = common_data.clip.weatherClip->getPrv(3, 140, &modPos, &base, thisx, count);
            if(priv != NULL){
                aWeatherSakura_ct(priv, play);
                priv->work[3]= 0;
                priv->work[4] = 313.0f + (RANDOM_F(521.0f));
                priv->currentY = y;
            }
        }
    }
}

void aWeatherSakura_ct(WeatherPrv* priv, UNUSED Game_Play* play){
    priv->work[0] = RANDOM_F(65535.0f);
    priv->work[1] = RANDOM_F(65535.0f);
    priv->work[2] = RANDOM_F(65535.0f);
}

s32 aWeatherSakura_CheckSakuraBorder(WeatherPrv* priv){
    UNUSED s32 pad; 
    Weather* weather = common_data.clip.weatherClip->actor;
    s32 ret = 0; 

    if(weather != NULL){
        xyz_t pos;
        f32 sakuraTemp;  
        pos = weather->pos;
        sakuraTemp =priv->pos.x;

        if(sakuraTemp < (pos.x + (-100.0f))){
            ret |= 2;
        }
        if(sakuraTemp > (pos.x + (100.0f))){
            ret |= 8;
        }
        sakuraTemp =priv->pos.z;

        if(sakuraTemp > (pos.z + (180.0f))){
            ret |= 4;
        }
        if(sakuraTemp < (pos.z + (-200.0f))){
            ret |= 1;
        }
    }

    return ret;
}

void aWeatherSakura_CheckSakuraScroll(WeatherPrv* priv){
    s32 border = aWeatherSakura_CheckSakuraBorder(priv);

    if(border != 0){
        if((border >> 1) & 1){
            priv->pos.x += 200.0f;
        }
        if((border >> 3) & 1){
            priv->pos.x -= 200.0f;
        }
        if((border >> 2) & 1){
            priv->pos.z -= 380.0f;
        }
        if(border & 1){
            priv->pos.z += 380.0f;
        }
    }

    if(common_data.clip.weatherClip != NULL){
        f32 y;
        Weather* weather = common_data.clip.weatherClip->actor;

        if(weather != NULL){
            y = 230.0f + weather->pos.y;
            if(priv->pos.y < + weather->pos.y){
                priv->pos.y = (y + (priv->pos.y - priv->currentY));
                priv->currentY = y; 
            }
        }
    }
}

void aWeatherSakura_SetWind2Sakura(WeatherPrv* priv){

    priv->pos.x += 0.9f;
}

void aWeatherSakura_move(WeatherPrv* priv, UNUSED Game_Play* play){

    priv->pos.x += priv->speed.x;
    priv->pos.y += priv->speed.y;
    priv->pos.z += priv->speed.z;
    
    priv->work[3] += priv->work[4];
    aWeatherSakura_SetWind2Sakura(priv);
    aWeatherSakura_CheckSakuraScroll(priv);
    priv->work[0] += 1024;
    priv->work[1] += 4536;
    priv->work[2] += 2280; 
}

void aWeatherSakura_set(Game_Play* play){

    OPEN_DISPS(play->state.gfxCtx);

    gSPDisplayList(POLY_XLU_DISP++, ef_hanabira01_00_setmode);

    
    CLOSE_DISPS(play->state.gfxCtx); 
}

void aWeatherSakura_draw(WeatherPrv* priv, Game_Play* play){
    UNUSED s32 pad; 
    xyz_t base = {0.05f, 0.05f, 0.05f};
    xyz_t pos;
    xyz_t screenPos; 

 
 
    pos.x = priv->pos.x + (6.0f * sin_s(priv->work[3]));

    pos.z = priv->pos.z + (6.0f * cos_s(priv->work[3]));
    pos.y = priv->pos.y; 
    Game_play_Projection_Trans(play, &pos, &screenPos);

    if((screenPos.x >= 0.0f) && (screenPos.x < SCREEN_WIDTH) && ( screenPos.y >= 0.0f) && (screenPos.y < SCREEN_HEIGHT)){
         Mtx* work = GRAPH_ALLOC(play->state.gfxCtx, sizeof(Mtx));

        OPEN_DISPS(play->state.gfxCtx); 
 
        suMtxMakeSRT(work, base.x, base.y, base.z, priv->work[2], priv->work[1], priv->work[2], pos.x, pos.y, pos.z);

        gSPMatrix(POLY_XLU_DISP++, work, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
 
        gSPDisplayList(POLY_XLU_DISP++, ef_hanabira01_00_modelT);
        
        CLOSE_DISPS( play->state.gfxCtx);

    }
}
