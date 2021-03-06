#include "k2EnginePreCompile.h"
#include "ShadowMapRender.h"



void ShadowMapRender::Init()
{
    float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    //近景用のシャドウマップ
    m_shadowMaps[0].Create(
        2048,
        2048,
        1,
        1,
        DXGI_FORMAT_R32_FLOAT,
        DXGI_FORMAT_D32_FLOAT,
        clearColor
    );
    //中景用のシャドウマップ
    m_shadowMaps[1].Create(
        1024,
        1024,
        1,
        1,
        DXGI_FORMAT_R32_FLOAT,
        DXGI_FORMAT_D32_FLOAT,
        clearColor
    );
    //遠景用のシャドウマップ
    m_shadowMaps[2].Create(
        512,
        512,
        1,
        1,
        DXGI_FORMAT_R32_FLOAT,
        DXGI_FORMAT_D32_FLOAT,
        clearColor
    );
}

void ShadowMapRender::Render(
    RenderContext& rc,
    int ligNo,
    Vector3& lightDirection,
    std::vector< IRenderer* >& renderObjects
)
{
    if (lightDirection.LengthSq() < 0.001f) {
        return;
    }
    m_cascadeShadowMapMatrix.CalcLightViewProjectionCropMatrix(lightDirection);

    int shadowMapNo = 0;
    for (auto& shadowMap : m_shadowMaps) {
        rc.WaitUntilToPossibleSetRenderTarget(shadowMap);
        rc.SetRenderTargetAndViewport(shadowMap);
        rc.ClearRenderTargetView(shadowMap);

        for (auto& renderer : renderObjects) {
            renderer->OnRenderShadowMap(
                rc, 
                ligNo,
                shadowMapNo, 
                m_cascadeShadowMapMatrix.GetLightViewProjectionCropMatrix(shadowMapNo)
            );
        }
        
        //描画が終わったらクリア
        m_renderers.clear();
        
        // 書き込み完了待ち
        rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);
        shadowMapNo++;
    }
}
  