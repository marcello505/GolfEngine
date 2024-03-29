//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_RENDERSHAPETYPE_H
#define SPC_PROJECT_RENDERSHAPETYPE_H

namespace GolfEngine::Scene::Render {
    enum class RenderShapeType {
        LineShape,
        CircleShape,
        RectShape,
        SpriteShape,
        ParticleSystemShape,
        TextRenderShape,
        ButtonRenderShape,
        TileMapRenderShape,
        GraphRenderShape
    };
}

#endif //SPC_PROJECT_RENDERSHAPETYPE_H
