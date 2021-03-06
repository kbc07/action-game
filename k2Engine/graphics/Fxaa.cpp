#include "k2EnginePreCompile.h"
#include "Fxaa.h"

void Fxaa::Init(RenderTarget& mainRenderTarget)
{
    // 最終合成用のスプライトを初期化する
    SpriteInitData spriteInitData;
    spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
    // 解像度はmainRenderTargetの幅と高さ
    spriteInitData.m_width = mainRenderTarget.GetWidth();
    spriteInitData.m_height = mainRenderTarget.GetHeight();
    // 2D用のシェーダーを使用する
    spriteInitData.m_fxFilePath = "Assets/shader/fxaa.fx";
    spriteInitData.m_vsEntryPointFunc = "VSMain";
    spriteInitData.m_psEntryPoinFunc = "PSMain";

    spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
    spriteInitData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();

    //解像度をGPUに送るための定数バッファを設定する。
    spriteInitData.m_expandConstantBuffer = (void*)&m_cB;
    spriteInitData.m_expandConstantBufferSize = sizeof(FaxxBuffer) + 
        (16 - (sizeof(FaxxBuffer) % 16));
    m_finalSprite.Init(spriteInitData);
}

void Fxaa::Render(RenderContext& rc, RenderTarget& mainRenderTarget)
{
    // レンダリングターゲットとして利用できるまで待つ
    rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
    // レンダリングターゲットを設定
    rc.SetRenderTargetAndViewport(mainRenderTarget);
    m_cB.bufferW = g_graphicsEngine->GetFrameBufferWidth();
    m_cB.bufferH = g_graphicsEngine->GetFrameBufferHeight();
    //描画。
    m_finalSprite.Draw(rc);
    // レンダリングターゲットへの書き込み終了待ち
    //メインレンダ―ターゲットをRENDERTARGETからPRESENTへ。
    rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
}
