#pragma once

#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <dxgi.h>

namespace rfg {
enum window_mode {
    WindowMode_Windowed = 0x0,
    WindowMode_Borderless = 0x1,
    WindowMode_Fullscreen = 0x2,
    WindowMode_Count = 0x3,
};

enum primitive_type {
    PrimitiveType_Invalid = 0xFFFFFFFF,
    PrimitiveType_TriangleList = 0x0,
    PrimitiveType_TriangleStrip = 0x1,
    PrimitiveType_LineList = 0x2,
    PrimitiveType_LineStrip = 0x3,
    PrimitiveType_QuadList = 0x4,
    PrimitiveType_Count = 0x5,
};

enum pixel_format {
    PixelFormat_None = 0x0,
    PixelFormat_Bc1 = 0x1,
    PixelFormat_Bc1_Gamma = 0x2,
    PixelFormat_Bc2 = 0x3,
    PixelFormat_Bc2_Gamma = 0x4,
    PixelFormat_Bc3 = 0x5,
    PixelFormat_Bc3_Gamma = 0x6,
    PixelFormat_Bc4 = 0x7,
    PixelFormat_Bc4_Gamma = 0x8,
    PixelFormat_Bc5 = 0x9,
    PixelFormat_Bc5_Gamma = 0xA,
    PixelFormat_Bc6H_SF16 = 0xB,
    PixelFormat_Bc6H_UF16 = 0xC,
    PixelFormat_Bc7 = 0xD,
    PixelFormat_Bc7_Gamma = 0xE,
    PixelFormat_Index4 = 0xF,
    PixelFormat_A4 = 0x10,
    PixelFormat_L4 = 0x11,
    PixelFormat_A8 = 0x12,
    PixelFormat_L8 = 0x13,
    PixelFormat_Index8 = 0x14,
    PixelFormat_L4A4 = 0x15,
    PixelFormat_G8R8 = 0x16,
    PixelFormat_R8G8 = 0x17,
    PixelFormat_R5G6B5 = 0x18,
    PixelFormat_R5G5B5A1 = 0x19,
    PixelFormat_R4G4B4A4 = 0x1A,
    PixelFormat_R5G5B5A3 = 0x1B,
    PixelFormat_Index14x2 = 0x1C,
    PixelFormat_R8G8B8 = 0x1D,
    PixelFormat_R8G8B8_Gamma = 0x1E,
    PixelFormat_R32F = 0x1F,
    PixelFormat_Y16X16 = 0x20,
    PixelFormat_A8R8G8B8 = 0x21,
    PixelFormat_A8R8G8B8_Gamma = 0x22,
    PixelFormat_X8R8G8B8 = 0x23,
    PixelFormat_X8R8G8B8_Gamma = 0x24,
    PixelFormat_A8B8G8R8 = 0x25,
    PixelFormat_A8B8G8R8_Gamma = 0x26,
    PixelFormat_R8G8B8A8 = 0x27,
    PixelFormat_R8G8B8A8_Gamma = 0x28,
    PixelFormat_A2R10G10B10F = 0x29,
    PixelFormat_A16B16G16R16F = 0x2A,
    PixelFormat_A32B32G32R32F = 0x2B,
    PixelFormat_Depth8 = 0x2C,
    PixelFormat_Depth16 = 0x2D,
    PixelFormat_Depth24Stencil8 = 0x2E,
    PixelFormat_ETC1_RGB8 = 0x2F,
    PixelFormat_ETC1_RGB8A4 = 0x30,
    PixelFormat_Pvrtc2 = 0x31,
    PixelFormat_Pvrtc4 = 0x32,
    PixelFormat_Pvrtc2A = 0x33,
    PixelFormat_Pvrtc4A = 0x34,
    PixelFormat_Ctx1 = 0x35,
    PixelFormat_DxN = 0x36,
    PixelFormat_Depth32F = 0x37,
    PixelFormat_Depth24FStencil8 = 0x38,
    PixelFormat_R11G11B10F = 0x39,
    PixelFormat_Depth32FStencil8 = 0x3A,
    PixelFormat_Depth16Stencil8 = 0x3B,
    PixelFormat_Count = 0x3C,
    PixelFormat_Invalid = 0x3C,
    PixelFormat_Native_RGBA32 = 0x27,
    PixelFormat_Native_RGBA32_Gamma = 0x28,
    PixelFormat_Default_Depth = 0x2E,
    PixelFormat_Dxt1 = 0x1,
    PixelFormat_Dxt1_Gamma = 0x2,
    PixelFormat_Dxt23 = 0x3,
    PixelFormat_Dxt23_Gamma = 0x4,
    PixelFormat_Dxt45 = 0x5,
    PixelFormat_Dxt45_Gamma = 0x6,
};

struct vertex_attribute_description {
    char id;
    char format;
    char inputStreamIndex;
    char instanceStepRate;
};

struct graphics_state_object {
    unsigned int hash;
    unsigned int refCount;
};

struct vertex_format : graphics_state_object {
    vertex_attribute_description attributes[17];
    unsigned int attributeOffsets[17];
    unsigned int attributeCount;
    unsigned int attributeIndices[17];
    unsigned int streamStride[6];
    unsigned int instanceDataStreamIndex;
};

struct render_geometry {
    vertex_format* pVertexFormat;
    ID3D11Buffer* pVertexBuffer;
    unsigned int vertexCount;
    ID3D11Buffer* pIndexBuffer;
    unsigned int indexCount;
    // Todo: Add type
    void* pSkinGeometry; // SoftwareSkinGeometry* pSkinGeometry;
    unsigned int skinningBufferOffset;
    const char* pDebugName;
    unsigned int indexFormat;
    unsigned int primitiveTopology;
    // Todo: Add type
    void* pMorphData; // SoftwareMorphData* pMorphData;
};

struct texture_description {
    unsigned __int16 width;
    unsigned __int16 height;
    unsigned __int16 depth;
    unsigned __int16 flags;
    char type;
    char format;
    char lutFormat;
    char multiSampleType;
    char addressModeU;
    char addressModeV;
    char addressModeW;
    char levelCount;
    char cpuAccessMode;
    char gpuAccessMode;
};

struct texture_data {
    texture_description description;
    ID3D11Resource* pTexture;
    ID3D11ShaderResourceView* pShaderView;
    DXGI_FORMAT d3dFormat;
};

// Todo: Make actual template for these
struct array__unsigned_char {
    char* m_pData;
    unsigned int m_size;
};
struct array__D3D11_SIGNATURE_PARAMETER_DESC {
    _D3D11_SIGNATURE_PARAMETER_DESC* m_pData;
    unsigned int m_size;
};

struct vertex_shader {
    // Array<unsigned char> shaderCode;
    array__unsigned_char shaderCode;
    ID3D11VertexShader* pVertexShader;
    // Array<_D3D11_SIGNATURE_PARAMETER_DESC> inputSignature;
    array__D3D11_SIGNATURE_PARAMETER_DESC inputSignature;
    unsigned int inputSignatureHash;
};

struct fragment_shader {
    ID3D11PixelShader* pPixelShader;
};

struct shader_pipeline {
    vertex_shader* pVertexShader;
    fragment_shader* pFragmentShader;
};

struct stock_objects {
    shader_pipeline m_shaderPipelines[3];
    vertex_shader* m_pStockVertexShaders[2];
    fragment_shader* m_pStockFragmentShaders[3];
    vertex_format* m_pFormats[3];
    texture_data m_textures[1];
};

struct blend_state : graphics_state_object {
    ID3D11BlendState* pState;
};

struct depth_stencil_state : graphics_state_object {
    ID3D11DepthStencilState* pState;
};

struct rasterizer_state : graphics_state_object {
    ID3D11RasterizerState* pState;
};

struct sampler_state : graphics_state_object {
    ID3D11SamplerState* pState;
};

struct vertex_input_binding : graphics_state_object {
    vertex_format* pVertexFormat;
    ID3D11InputLayout* pLayout;
    unsigned int geometryModeMask;
};

template <class T> class sized_array {
    T* data;
    unsigned int size;
    unsigned int capacity;
};

struct memory_block {
    char* pStart;
    unsigned int size;
};

struct base_pool_allocator // 24 bytes
{
    memory_block m_memoryBlock;
    unsigned int m_capacity;
    unsigned int m_size;
    unsigned int m_elementSize;
    unsigned int m_firstFreeIndex;
};

template <class T>
class pool_allocator // 24 bytes
{
    base_pool_allocator m_pool;
};

struct graphics_state_object_cache {
    char m_stateObjects[45];
    // HashMap<unsigned int, GraphicsStateObject *, DefaultHashmapTraits<unsigned int,
    // GraphicsStateObject *> > m_stateObjects;
};

template <class T> class graphics_state_object_pool {
    pool_allocator<char> m_allocator;
    // PoolAllocator<VertexInputBinding> m_allocator;
    graphics_state_object_cache m_cache;
    unsigned int m_peakSize;
    unsigned int m_cacheHits;
    unsigned int m_cacheRequests;
};

struct combined_graphics_state_object_pool {
    graphics_state_object_pool<blend_state> m_blendStatePool;
    graphics_state_object_pool<rasterizer_state> m_rasterizerStatePool;
    graphics_state_object_pool<sampler_state> m_samplerStatePool;
    graphics_state_object_pool<depth_stencil_state> m_depthStencilStatePool;
    graphics_state_object_pool<vertex_format> m_vertexFormatPool;
    graphics_state_object_pool<vertex_input_binding> m_vertexInputBindingPool;
};

struct data_buffer {
    char* m_pCurrentPosition;
    char* m_pEnd;
    char* m_pBufferStart;
};

struct skinning_batch {
    // SkinningD3D11* pSkinningBuffer;
    void* pSkinningBuffer;

    char* pMappedBufferData;
};

struct skinned_geometry_instance {
    ID3D11Buffer* pVertexBuffer;
    char* pMappedData;
    unsigned int skinBufferOffset;
};

struct skinning_d3d11 {
    ID3D11Buffer* m_pSkinningBuffer;
    skinning_batch m_skinningBatch;
    sized_array<skinned_geometry_instance> m_instances[2];
    unsigned int m_currentFrameIndex;
    unsigned int m_currentBufferPosition;
    unsigned int m_size;
    unsigned int m_bufferSize;
    // SoftwareSkinningJointMatrixData* m_pSkinningJointMatrices;
    void* m_pSkinningJointMatrices;

    unsigned int m_currentJointMatricesPosition;
    // TaskQueue* m_pTaskQueue;
    void* m_pTaskQueue;

    data_buffer m_morphBuffer;
    unsigned int m_morphBufferSize;
    void* m_pMorphBufferData;
};

struct graphics_command_buffer {
    ID3D11DeviceContext* pContext;
    ID3D11Buffer* pMappedConstantBuffer;
    // RenderTarget* pCurrentRenderTarget;
    void* pCurrentRenderTarget;

    skinning_d3d11* pSkinningBuffer;
    ID3D11Buffer* pImmediateVertexData;
    unsigned int immediateVertexBufferOffset;
    unsigned int immediateVertexBufferSize;
    unsigned int immediateVertexDataStride;
    unsigned int immediateVertexCount;
    primitive_type immediatePrimitiveType;
    // DownsampleDepthContext* pDownsampleDepthContext;
    void* pDownsampleDepthContext;

    vertex_format* pCurrentlyBoundVertexFormat;
    void* pRenderCommandBufferStorage;
    bool quadlistImmediateCommand;
    char* pCurrentImmediateBuffer;
    char quadBuffer[65536];
};

struct render_target_buffer {
    pixel_format format;
    texture_data* pDataBuffer;
};

struct render_target {
    ID3D11RenderTargetView* renderTargetViews[8];
    ID3D11DepthStencilView* pDepthBufferView;
    render_target_buffer colorBuffers[8];
    render_target_buffer depthBuffer;
    unsigned int colorBufferCount;
    unsigned int width;
    unsigned int height;
};

struct graphics_system;
struct render_swap_chain {
    graphics_system* pGraphicsSystem;
    pixel_format depthBufferFormat;
    HWND__* windowHandle;
    texture_data backBufferColorData;
    texture_data backBufferDepthData;
    render_target backBufferRenderTarget;
    render_target noGammaBackBufferRenderTarget;
    IDXGISwapChain* pSwapChain;
    DXGI_SWAP_CHAIN_DESC swapChainDescription;
    ID3D11RenderTargetView* pBackBufferRenderTargetView;
    ID3D11RenderTargetView* pNoGammaBackBufferRenderTargetView;
    ID3D11DepthStencilView* pBackBufferDepthView;
    unsigned int windowWidth;
    unsigned int windowHeight;
    unsigned int presentationInterval;
};

struct graphics_system_base {
    // ShaderFactory* pShaderFactory;
    // MemoryAllocator* pSystemAllocator;
    void* pShaderFactory;
    void* pSystemAllocator;

    combined_graphics_state_object_pool stateObjectPool;
    stock_objects stockObjects;
};

struct graphics_system : graphics_system_base {
    ID3D11Device* pDevice;
    ID3D11DeviceContext* pImmediateContext;
    float screenAspectRatio;
    HWND__* createdWindowHandle;
    bool isWindowDestroyed;
    skinning_d3d11 skinningBuffer;
    unsigned int ownerThreadId;
    unsigned int frontThreadId;
    graphics_command_buffer immediateCommandBuffer;
    graphics_command_buffer deferredCommandBuffer;
    fragment_shader emptyFragmentShader;
    render_swap_chain* pDefaultSwapChain;
    render_swap_chain* pCurrentSwapChain;

    unsigned int currentFrameNumber;
    // ScreenCapture* pScreenCapture;
    void* pScreenCapture;

    window_mode previousFullscreenMode;
    window_mode fullscreenMode;
    unsigned int exclusiveModeWidth;
    unsigned int exclusiveModeHeight;
    unsigned int exclusiveModeRefreshRateNumerator;
    unsigned int exclusiveModeRefreshRateDenominator;
    unsigned int windowModeWidth;
    unsigned int windowModeHeight;
};
} // namespace rfg