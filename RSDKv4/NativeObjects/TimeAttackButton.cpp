#include "RetroEngine.hpp"

void TimeAttackButton_Create(void *objPtr)
{
    RSDK_THIS(TimeAttackButton);
    entity->textureCircle = LoadTexture("Data/Game/Menu/Circle.png", TEXFMT_RGBA4444);

    int texture            = LoadTexture("Data/Game/Menu/Intro.png", TEXFMT_RGBA4444);
    entity->meshTimeAttack = LoadMesh("Data/Game/Models/TimeAttack.bin", texture);
    SetMeshAnimation(entity->meshTimeAttack, &entity->animator, 0, 16, 0.0);
    entity->animator.loopAnimation = true;
    entity->translateX             = 0.0;
    entity->translateY             = 16.0;
    entity->translateZ             = 160.0;
    entity->r                      = 0xFF;
    entity->g                      = 0xFF;
    entity->b                      = 0x00;
    entity->labelPtr               = CREATE_ENTITY(TextLabel);
    entity->labelPtr->fontID       = 0;
    entity->labelPtr->textScale    = 0.15;
    entity->labelPtr->textAlpha    = 0;
    entity->labelPtr->state    = 0;
    SetStringToFont(entity->labelPtr->text, strTimeAttack, 0);
    entity->labelPtr->alignPtr(entity->labelPtr, 1);
}
void TimeAttackButton_Main(void *objPtr)
{
    RSDK_THIS(TimeAttackButton);

    if (entity->visible) {
        if (entity->scale < 0.2) {
            entity->scale += ((0.25 - entity->scale) / ((60.0 * Engine.deltaTime) * 16.0));
            if (entity->scale > 0.2)
                entity->scale = 0.2;
        }
        SetRenderBlendMode(RENDER_BLEND_ALPHA);
        SetRenderVertexColor(entity->r, entity->g, entity->b);
        RenderImage(entity->translateX, entity->translateY, entity->translateZ, entity->scale, entity->scale, 256.0, 256.0, 512.0, 512.0, 0.0, 0.0,
                    255, entity->textureCircle);
        SetRenderVertexColor(0xFF, 0xFF, 0xFF);
        SetRenderBlendMode(RENDER_BLEND_NONE);

        entity->angle -= Engine.deltaTime;
        if (entity->angle < -(M_PI * 2))
            entity->angle += (M_PI * 2);

        entity->animator.animationSpeed = Engine.deltaTime * 16.0;
        AnimateMesh(entity->meshTimeAttack, &entity->animator);

        NewRenderState();
        matrixRotateXYZF(&entity->renderMatrix, 0.0, sinf(entity->angle) * 0.5, 0.0);
        matrixTranslateXYZF(&entity->matrix2, entity->translateX, entity->translateY, entity->translateZ - 8.0);
        matrixMultiplyF(&entity->renderMatrix, &entity->matrix2);
        SetRenderMatrix(&entity->renderMatrix);
        RenderMesh(entity->meshTimeAttack, 1, true);
        SetRenderMatrix(NULL);

        NativeEntity_TextLabel *label = entity->labelPtr;
        label->textX                  = entity->translateX;
        label->textY                  = entity->translateY - 72.0;
        label->textZ                  = entity->translateZ;
        if (label->textX <= -8.0 || label->textX >= 8.0) {
            if (label->textAlpha > 0)
                label->textAlpha -= 8;
        }
        else {
            if (label->textAlpha < 0x100)
                label->textAlpha += 8;
        }
    }
}