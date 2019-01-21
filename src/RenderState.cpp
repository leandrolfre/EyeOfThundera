#include "RenderState.h"

RenderState::RenderState() 
{
}

RenderState::~RenderState() 
{
}

void RenderState::init() 
{
    Depth  = {  true, //enable
                true,  //depthMask
                Func::LESS //func
             };

    Blend = {   true, //enable
                BlendMode::SRC_ALPHA, //srcBlend
                BlendMode::ONE_MINUS_SRC_ALPHA //dstBlend
            };

    Stencil = { true, //enable
                0xFF, //writeMask
                0xFF, //funcMask
                1, //funcRef
                Func::EQUAL, //func 
                StencilOp::KEEP, //stencilFail
                StencilOp::KEEP , //depthFail
                StencilOp::KEEP  //bothPass
              };

    CullFace = { true, //enable
                 CullFaceOrder::CCW,
                 CullFaceMode::BACK
               };
}