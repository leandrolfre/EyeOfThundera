#pragma once

enum class BlendMode
{
    ZERO,
    ONE,
    SRC_COLOR,
    ONE_MINUS_SRC_COLOR,
    DST_COLOR,
    ONE_MINUS_DST_COLOR,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA,
    DST_ALPHA,
    ONE_MINUS_DST_ALPHA,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA
};

enum class Func
{
    ALWAYS,
    NEVER,
    LESS,
    EQUAL,
    LESS_EQUAL,
    GREATER,
    NOT_EQUAL,
    GREATER_EQUAL
};

enum class StencilOp
{
    KEEP,
    ZERO,
    REPLACE,
    INCR,
    INCR_WRAP,
    DECR,
    DECR_WRAP,
    INVERT
};

enum class CullFaceMode
{
    BACK,
    FRONT,
    BOTH
};

enum class CullFaceOrder
{
    CCW,
    CW
};

struct Blend
{
    bool enable;
    BlendMode blendSrc;
    BlendMode blendDst;
};

struct Depth
{
    bool enable;
    bool depthMask;
    Func func;
};

struct Stencil
{
    bool enable;
    unsigned int writeMask;
    unsigned int funcMask;
    int funcRef;
    Func func;
    StencilOp stencilFail;
    StencilOp depthFail;
    StencilOp bothPass;
};

struct CullFace
{
    bool enable;
    CullFaceOrder order;
    CullFaceMode mode;
};

class RenderState
{
public:
	RenderState();
	~RenderState();
	void init();
    
    CullFace CullFace;
    Stencil Stencil;
    Depth Depth;
    Blend Blend;
    
};