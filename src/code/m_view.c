#include "m_view.h"
#include "gfx.h"
#include "macros.h"
#include "main.h"
#include "sys_matrix.h"

s32 D_8010EF00_jp = 1;

void set_viewport(Vp* vp, Viewport* viewport) {
    s32 width = viewport->rightX - viewport->leftX;
    s32 height = viewport->bottomY - viewport->topY;

    vp->vp.vscale[0] = width * 2;
    vp->vp.vscale[1] = height * 2;
    vp->vp.vscale[2] = 511;
    vp->vp.vscale[3] = 0;

    vp->vp.vtrans[0] = (width + viewport->leftX * 2) * 2;
    vp->vp.vtrans[1] = (height + viewport->topY * 2) * 2;
    vp->vp.vtrans[2] = 511;
    vp->vp.vtrans[3] = 0;
}

void initView(View* view, GraphicsContext* graph) {
    if (D_8010EF00_jp) {}

    view->gfxCtx = graph;

    view->viewport.topY = 0;
    view->viewport.bottomY = SCREEN_HEIGHT;
    view->viewport.leftX = 0;
    view->viewport.rightX = SCREEN_WIDTH;
    view->unk_000 = 1234;

    view->fovY = 20.0f;
    view->scale = 1.0f;
    view->near = 200.0f;
    view->far = 1600.0f;

    view->eye.x = 0.0f;
    view->eye.y = 0.0f;
    view->eye.z = -1.0f;
    view->at.x = 0.0f;
    view->at.x = 0.0f;
    view->at.x = 0.0f;
    view->up.x = 0.0f;
    view->up.y = 1.0f;
    view->up.z = 0.0f;

    if (D_8010EF00_jp != 0) {
        D_8010EF00_jp = 0;
    }

    view->flag = 7;
    stretchViewInit(view);
}

void setLookAtView(View* view, xyz_t* eye, xyz_t* at, xyz_t* up) {
    if (eye->x == at->x && eye->z == at->z) {
        eye->x += 0.1f;
    }

    view->eye = *eye;
    view->at = *at;
    view->up = *up;

    view->flag |= 1;
}

void getLookAtView(View* view, xyz_t* eye, xyz_t* at, xyz_t* up) {
    view->eye = *eye;
    view->at = *at;
    view->up = *up;
}

void setScaleView(View* view, f32 scale) {
    view->scale = scale;

    view->flag |= 4;
}

void getScaleView(View* view, f32* scale) {
    *scale = view->scale;
}

void setPerspectiveView(View* view, f32 fovY, f32 near, f32 far) {
    view->fovY = fovY;
    view->near = near;
    view->far = far;

    view->flag |= 4;
}

void getPerspectiveView(View* view, f32* fovY, f32* near, f32* far) {
    *fovY = view->fovY;
    *near = view->near;
    *far = view->far;
}

void setScissorView(View* view, Viewport* viewport) {
    view->viewport = *viewport;

    view->flag |= 2;
}

void getScissorView(View* view, Viewport* viewport) {
    *viewport = view->viewport;
}

void setScissorX(Gfx** gfxP, s32 leftX, s32 topY, s32 rightX, s32 bottomY) {
    Gfx* gfx = *gfxP;

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, leftX, topY, rightX, bottomY);
    *gfxP = gfx;
}

void setScissorOvl(View* view, Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s32 left = view->viewport.leftX;
    s32 top = view->viewport.topY;
    s32 right = view->viewport.rightX;
    s32 bottom = view->viewport.bottomY;

    gDPPipeSync(gfx++);
    setScissorX(&gfx, left, top, right, bottom);
    *gfxP = gfx;
}

void setScissor(View* view) {
    GraphicsContext* graph = view->gfxCtx;
    Gfx* gfx;
    s32 left = view->viewport.leftX;
    s32 top = view->viewport.topY;
    s32 right = view->viewport.rightX;
    s32 bottom = view->viewport.bottomY;

    OPEN_DISPS(graph);

    gfx = POLY_OPA_DISP;
    setScissorX(&gfx, left, top, right, bottom);
    POLY_OPA_DISP = gfx;

    gfx = POLY_XLU_DISP;
    setScissorX(&gfx, left, top, right, bottom);
    POLY_XLU_DISP = gfx;

    gfx = SHADOW_DISP;
    setScissorX(&gfx, left, top, right, bottom);
    SHADOW_DISP = gfx;

    gfx = LIGHT_DISP;
    setScissorX(&gfx, left, top, right, bottom);
    LIGHT_DISP = gfx;

    CLOSE_DISPS(graph);
}

s32 stretchViewInit(View* view) {
    view->stretch.targetRotate.x = 0.0f;
    view->stretch.targetRotate.y = 0.0f;
    view->stretch.targetRotate.z = 0.0f;

    view->stretch.targetScale.x = 1.0f;
    view->stretch.targetScale.y = 1.0f;
    view->stretch.targetScale.z = 1.0f;

    view->stretch.rotate = view->stretch.targetRotate;
    view->stretch.scale = view->stretch.targetScale;
    view->stretch.step = 0.0f;

    return 0;
}

s32 do_stretch_view(View* view, Mtx* mtx) {
    if (view->stretch.step == 0.0f) {
        return FALSE;
    } else if (view->stretch.step == 1.0f) {
        view->stretch.rotate = view->stretch.targetRotate;
        view->stretch.scale = view->stretch.targetScale;
        view->stretch.step = 0.0f;
    } else {
        view->stretch.rotate.x += (view->stretch.targetRotate.x - view->stretch.rotate.x) * view->stretch.step;
        view->stretch.rotate.y += (view->stretch.targetRotate.y - view->stretch.rotate.y) * view->stretch.step;
        view->stretch.rotate.z += (view->stretch.targetRotate.z - view->stretch.rotate.z) * view->stretch.step;

        view->stretch.scale.x += (view->stretch.targetScale.x - view->stretch.scale.x) * view->stretch.step;
        view->stretch.scale.y += (view->stretch.targetScale.y - view->stretch.scale.y) * view->stretch.step;
        view->stretch.scale.z += (view->stretch.targetScale.z - view->stretch.scale.z) * view->stretch.step;
    }

    {
        MtxF mtxF;
        s_xyz rot;

        rot.x = view->stretch.rotate.x * 10430.378f;
        rot.y = view->stretch.rotate.y * 10430.378f;
        rot.z = view->stretch.rotate.z * 10430.378f;

        Matrix_MtxtoMtxF(mtx, &mtxF);
        Matrix_put(&mtxF);

        Matrix_RotateX(rot.x, 1);
        Matrix_RotateY(rot.y, 1);
        Matrix_RotateZ(rot.z, 1);

        Matrix_scale(view->stretch.scale.x, view->stretch.scale.y, view->stretch.scale.z, TRUE);

        Matrix_RotateZ(-rot.z, 1);
        Matrix_RotateY(-rot.y, 1);
        Matrix_RotateX(-rot.x, 1);

        _Matrix_to_Mtx(mtx);
    }

    return TRUE;
}

s32 showView(View* view, s32 flagMask) {
    flagMask = ((view->flag & flagMask) | (flagMask >> 4));

    if (flagMask & 8) {
        return showOrthoView(view);
    } else {
        return showPerspectiveView(view);
    }
}

s32 showPerspectiveView(View* view) {
    GraphicsContext* graph = view->gfxCtx;
    f32 aspect;
    s32 width;
    s32 height;
    Vp* vp;
    Mtx* mtx;

    OPEN_DISPS(graph);

    vp = GRAPH_ALLOC(graph, sizeof(Vp));
    set_viewport(vp, &view->viewport);
    view->vp = *vp;

    setScissor(view);

    gSPViewport(POLY_OPA_DISP++, vp);
    gSPViewport(POLY_XLU_DISP++, vp);
    gSPViewport(SHADOW_DISP++, vp);
    gSPViewport(LIGHT_DISP++, vp);

    mtx = GRAPH_ALLOC(graph, sizeof(Mtx));

    view->projectionMtxPtr = mtx;

    width = view->viewport.rightX - view->viewport.leftX;
    height = view->viewport.bottomY - view->viewport.topY;
    aspect = (f32)width / (f32)height;
    guPerspective(mtx, &view->normal, view->fovY, aspect, view->near, view->far, view->scale);

    view->projectionMtx = *mtx;

    do_stretch_view(view, mtx);

    gSPPerspNormalize(POLY_OPA_DISP++, view->normal);
    gSPMatrix(POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    gSPPerspNormalize(POLY_XLU_DISP++, view->normal);
    gSPMatrix(POLY_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    gSPPerspNormalize(SHADOW_DISP++, view->normal);
    gSPMatrix(SHADOW_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    gSPPerspNormalize(LIGHT_DISP++, view->normal);
    gSPMatrix(LIGHT_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    mtx = GRAPH_ALLOC(graph, sizeof(Mtx));
    view->viewingMtxPtr = mtx;

    if ((view->eye.x == view->at.x) && (view->eye.y == view->at.y) && (view->eye.z == view->at.z)) {
        view->eye.x += 1.0f;
        view->eye.y += 1.0f;
        view->eye.z += 1.0f;
    }
    guLookAt(mtx, view->eye.x, view->eye.y, view->eye.z, view->at.x, view->at.y, view->at.z, view->up.x, view->up.y,
             view->up.z);

    view->viewingMtx = *mtx;

    gSPMatrix(POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    gSPMatrix(POLY_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    gSPMatrix(SHADOW_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    gSPMatrix(LIGHT_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    CLOSE_DISPS(graph);

    return TRUE;
}

s32 showOrthoView(View* view) {
    GraphicsContext* graph = view->gfxCtx;
    Vp* vp;
    Mtx* mtx;

    OPEN_DISPS(graph);

    vp = GRAPH_ALLOC(graph, sizeof(Vp));
    set_viewport(vp, &view->viewport);
    view->vp = *vp;

    setScissor(view);

    gSPViewport(POLY_OPA_DISP++, vp);
    gSPViewport(POLY_XLU_DISP++, vp);
    gSPViewport(SHADOW_DISP++, vp);
    gSPViewport(LIGHT_DISP++, vp);
    gSPViewport(OVERLAY_DISP++, vp);

    mtx = GRAPH_ALLOC(graph, sizeof(Mtx));
    view->projectionMtxPtr = mtx;

    guOrtho(mtx, -(f32)ScreenWidth / 2.0f, (f32)ScreenWidth / 2.0f, -(f32)ScreenHeight / 2.0f, (f32)ScreenHeight / 2.0f,
            view->near, view->far, view->scale);

    view->projectionMtx = *mtx;

    gSPMatrix(POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    gSPMatrix(POLY_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    gSPMatrix(SHADOW_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    gSPMatrix(LIGHT_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    CLOSE_DISPS(graph);

    return TRUE;
}

s32 showOverLayView(View* view) {
    GraphicsContext* graph = view->gfxCtx;
    Gfx* gfx;
    Vp* vp;

    Mtx* mtx;

    OPEN_DISPS(graph);

    vp = GRAPH_ALLOC(graph, sizeof(Vp));
    set_viewport(vp, &view->viewport);
    view->vp = *vp;

    gDPPipeSync(OVERLAY_DISP++);

    gfx = OVERLAY_DISP;
    setScissorX(&gfx, view->viewport.leftX, view->viewport.topY, view->viewport.rightX, view->viewport.bottomY);
    OVERLAY_DISP = gfx;

    gSPViewport(OVERLAY_DISP++, vp);

    mtx = GRAPH_ALLOC(graph, sizeof(Mtx));
    view->projectionMtxPtr = mtx;

    guOrtho(mtx, -(f32)ScreenWidth / 2.0f, (f32)ScreenWidth / 2.0f, -(f32)ScreenHeight / 2.0f, (f32)ScreenHeight / 2.0f,
            view->near, view->far, view->scale);

    view->projectionMtx = *mtx;

    gSPMatrix(OVERLAY_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    CLOSE_DISPS(graph);

    return TRUE;
}

s32 showPerspectiveOverLayView(View* view) {
    UNUSED s32 pad;
    Gfx* gfx;
    UNUSED s32 pad2;
    GraphicsContext* graph = view->gfxCtx;
    f32 aspect;
    s32 width;
    s32 height;
    Vp* vp;
    Mtx* mtx;

    OPEN_DISPS(graph);

    vp = GRAPH_ALLOC(graph, sizeof(Vp));
    set_viewport(vp, &view->viewport);
    view->vp = *vp;

    gDPPipeSync(OVERLAY_DISP++);

    gfx = OVERLAY_DISP;
    setScissorX(&gfx, view->viewport.leftX, view->viewport.topY, view->viewport.rightX, view->viewport.bottomY);
    OVERLAY_DISP = gfx;

    gSPViewport(OVERLAY_DISP++, vp);

    mtx = GRAPH_ALLOC(graph, sizeof(Mtx));

    view->projectionMtxPtr = mtx;

    width = view->viewport.rightX - view->viewport.leftX;
    height = view->viewport.bottomY - view->viewport.topY;
    aspect = (f32)width / (f32)height;
    guPerspective(mtx, &view->normal, view->fovY, aspect, view->near, view->far, view->scale);

    view->projectionMtx = *mtx;
    gSPPerspNormalize(OVERLAY_DISP++, view->normal);
    gSPMatrix(OVERLAY_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    mtx = GRAPH_ALLOC(graph, sizeof(Mtx));
    view->viewingMtxPtr = mtx;

    if ((view->eye.x == view->at.x) && (view->eye.y == view->at.y) && (view->eye.z == view->at.z)) {
        view->eye.x += 1.0f;
        view->eye.y += 1.0f;
        view->eye.z += 1.0f;
    }
    guLookAt(mtx, view->eye.x, view->eye.y, view->eye.z, view->at.x, view->at.y, view->at.z, view->up.x, view->up.y,
             view->up.z);

    view->viewingMtx = *mtx;

    gSPMatrix(OVERLAY_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    CLOSE_DISPS(graph);

    return TRUE;
}

s32 showOrthoView1(View* view, Gfx** gfxPtr) {
    Gfx* gfx;
    GraphicsContext* graph;
    Mtx* mtx;
    Vp* vp;

    gfx = *gfxPtr;
    graph = view->gfxCtx;

    vp = GRAPH_ALLOC(graph, sizeof(Vp));
    set_viewport(vp, &view->viewport);
    view->vp = *vp;

    setScissorOvl(view, &gfx);

    gSPViewport(gfx++, vp);

    mtx = GRAPH_ALLOC(graph, sizeof(Mtx));
    view->projectionMtxPtr = mtx;

    guOrtho(mtx, (f32)ScreenWidth * -0.5f, (f32)ScreenWidth * 0.5f, (f32)ScreenHeight * -0.5f, (f32)ScreenHeight * 0.5f,
            view->near, view->far, view->scale);

    view->projectionMtx = *mtx;

    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    *gfxPtr = gfx;

    return TRUE;
}

s32 showView1(View* view, s32 flagMask, Gfx** gfxPtr) {
    Gfx* gfx;
    s32 width;
    Gfx* gfxSave;
    s32 height;
    GraphicsContext* graph;
    Mtx* projection;
    Mtx* viewMtx;
    Vp* vp;

    graph = view->gfxCtx;
    gfx = *gfxPtr;
    flagMask = (flagMask & view->flag) | (flagMask >> 4);

    if (flagMask & 2) {
        vp = GRAPH_ALLOC(graph, sizeof(Vp));
        set_viewport(vp, &view->viewport);
        view->vp = *vp;

        gDPPipeSync(gfx++);
        {
            gfxSave = gfx;
            setScissorX(&gfxSave, view->viewport.leftX, view->viewport.topY, view->viewport.rightX,
                        view->viewport.bottomY);
            gfx = gfxSave;
        }
        gSPViewport(gfx++, vp);
    }

    if (flagMask & 8) {
        projection = GRAPH_ALLOC(graph, sizeof(Mtx));

        view->projectionMtxPtr = projection;
        guOrtho(projection, -(f32)ScreenWidth / 2.0f, (f32)ScreenWidth / 2.0f, -(f32)ScreenHeight / 2.0f,
                (f32)ScreenHeight / 2.0f, view->near, view->far, view->scale);

        view->projectionMtx = *projection;
        gSPMatrix(gfx++, projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    } else if (flagMask & 6) {
        viewMtx = GRAPH_ALLOC(graph, sizeof(Mtx));

        view->projectionMtxPtr = viewMtx;

        width = view->viewport.rightX - view->viewport.leftX;
        height = view->viewport.bottomY - view->viewport.topY;
        guPerspective(viewMtx, &view->normal, view->fovY, (f32)width / (f32)height, view->near, view->far, view->scale);

        view->projectionMtx = *viewMtx;
        gSPPerspNormalize(gfx++, view->normal);
        gSPMatrix(gfx++, viewMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    }

    if (flagMask & 1) {
        viewMtx = GRAPH_ALLOC(graph, sizeof(Mtx));

        view->viewingMtxPtr = viewMtx;
        guLookAt(viewMtx, view->eye.x, view->eye.y, view->eye.z, view->at.x, view->at.y, view->at.z, view->up.x,
                 view->up.y, view->up.z);

        view->viewingMtx = *viewMtx;
        gSPMatrix(gfx++, viewMtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    }

    view->flag = 0;
    *gfxPtr = gfx;

    return TRUE;
}
