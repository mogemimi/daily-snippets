# Low Level Graphics API Cheatsheet

* **Direct3D 11**: [MSDN](https://msdn.microsoft.com/en-us/library/windows/desktop/ff476080.aspx), [Direct3D 11 Reference](https://msdn.microsoft.com/en-us/library/windows/desktop/ff476147.aspx)
* **OpenGL 4**: [Homepage](https://www.opengl.org/), [Reference Pages](https://www.opengl.org/sdk/docs/man/)
* **Metal**: [Homepage](https://developer.apple.com/metal/), [Framework Reference](https://developer.apple.com/library/ios/documentation/Metal/Reference/MetalFrameworkReference/index.html)
* XNA Game Studio 4.0 (and MonoGame): [MSDN](https://msdn.microsoft.com/en-US/bb200104.aspx)

>:bulb: Issues and pull requests are always welcome. [DirectX 12](http://blogs.msdn.com/b/directx/p/directx12.aspx), Mantle, GL ES, WebGL and glNext are not yet supported but we will gladly accept pull requests.

":pencil2: (pencil emoji)" means "work-in-progress".

## Table of Contents

* [Words](#words)
* [Render Commands](#render-commands)
  * [Clear](#clear)
  * [Draw](#draw)
  * [Draw Indexed](#draw-indexed)
  * [Draw Instanced](#draw-instanced)
  * [Draw Indexed Instanced](#draw-indexed-instanced)
  * [Index Element Size](#index-element-size)
  * [Primitive Topology](#primitive-topology)
  * [Viewport](#viewport)
  * [Scissor Rectangle](#scissor-rectangle)
* [Pipeline State](#pipeline-state)
  * [Input Layout](#input-layout)
    * [Step Rate](#step-rate)
    * [Vertex Declaration](#vertex-declaration)
    * [Vertex Element Format](#vertex-element-format)
* [Shaders](#shaders)
  * [Create and Compile Shader](#create-and-compile-shader)
  * [Shader Language](#shader-language)
* [Render States](#render-states)
  * [Blend](#blend)
    * [Blend Function](#blend-function)
    * [Blend Factor](#blend-factor)
  * [Depth Stencil](#depth-stencil)
    * [Comparison Function](#comparison-function)
    * [Stencil Operation](#stencil-operation)
  * [Rasterizer](#rasterizer)
    * [Cull Mode](#cull-mode)
    * [Fill Mode](#fill-mode)
    * [Scissor Test](#scissor-test)
  * [Sampler](#sampler)
    * [Create Sampler](#create-sampler)
    * [Apply Sampler](#apply-sampler)
    * [Texture Address Mode](#texture-address-mode)
    * [Texture Filter](#texture-filter)
* [Buffers](#buffers)
  * [Create Constant Buffer](#create-constant-buffer)
  * [Create Index Buffer](#create-index-buffer)
  * [Create Vertex Buffer](#create-vertex-buffer)
  * [Static Buffer](#static-buffer)
  * [Dynamic Buffer](#dynamic-buffer)
* [Textures](#textures)
  * [Texture 1D](#texture-1d)
  * [Texture 2D](#texture-2d)
  * [Texture 3D](#texture-3d)
* [Render Target](#render-target)
* [Pixel Formats](#pixel-format)
  * [Surface Format](#surface-format)
  * [Depth Format](#depth-format)

----

## Words

|Direct3D 11|XNA 4.0|OpenGL 4|Metal|
|:----------|:------|:-------|:----|
|_DESC       |--                    |--                            |Descriptor|
|VertexShader|VertexShader          |VertexShader                  |VertexFunction|
|PixelShader |PixelShader           |FragmentShader                |FragmentFunction|
|InputLayout |VertexBufferBinding(s)|VertexArray & VertexAttributes|VertexLayout|
|StepRate    |InstanceFrequency     |VertexAttribDivisor           |StepRate|
|?|RenderTarget|Framebuffer|?|
|BLEND_OP (Blending Operation)|BlendFunction|?|?|
|BLEND (Blend Factor)|Blend|?|?|

----

## Render Commands

### Clear

**OpenGL 4**
```cpp
glClearDepth(depth);
glClearStencil(stencil);
glClearColor(colorVector.X, colorVector.Y, colorVector.Z, colorVector.W);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
```

**Direct3D 11**
```cpp
deviceContext->ClearRenderTargetView(renderTarget->RenderTargetView(), fillColor.Data());
deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
```

**Metal**
```objective-c
MTLRenderPassDescriptor* renderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
renderPassDescriptor.colorAttachments[0].texture = texture;
renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.65f, 0.65f, 0.65f, 1.0f);
renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
```

### Draw

**OpenGL 4**
```cpp
glDrawArrays(primitiveTopology, 0, vertexCount);
```

**Direct3D 11**
```cpp
deviceContext->IASetPrimitiveTopology(primitiveTopology);

deviceContext->Draw(vertexCount, 0);
```

**Metal**
```objective-c
// Draw
[renderEncoder drawPrimitives ...];
```

### Draw Indexed

**OpenGL 4**
```cpp
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

glDrawElements(primitiveTopology, indexCount, indexElementSize, nullptr);
```

**Direct3D 11**
```cpp
deviceContext->IASetIndexBuffer(indexBuffer, indexElementSize, 0);
deviceContext->IASetPrimitiveTopology(primitiveTopology);

deviceContext->DrawIndexed(indexCount, 0, 0);
```

**Metal**
```objective-c
// DrawIndexed
[renderEncoder drawIndexedPrimitives ...];
```

### Draw Instanced

**OpenGL 4**
```cpp
glDrawArraysInstanced(primitiveTopology, 0, vertexCount, instanceCount);
```

**Direct3D 11**
```cpp
deviceContext->IASetPrimitiveTopology(primitiveTopology);

deviceContext->DrawInstanced(vertexCount, instanceCount, 0, 0);
```

**Metal**

```objective-c
// DrawInstanced
[renderEncoder drawPrimitives ...];
```

### Draw Indexed Instanced

**OpenGL 4**

```cpp
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

glDrawElementsInstanced(primitiveTopology, indexCount, indexElementSize,
  nullptr, instanceCount);
```

**Direct3D 11**

```cpp
deviceContext->IASetIndexBuffer(indexBuffer, indexElementSize, 0);
deviceContext->IASetPrimitiveTopology(primitiveTopology);

deviceContext->DrawIndexedInstanced(indexCount, instanceCount, 0, 0, 0);
```

**Metal**
```objective-c
// DrawIndexedInstanced
[renderEncoder drawIndexedPrimitives ...];
```

### Index Element Size

**Direct3D 11**

```cpp
DXGI_FORMAT_R16_UINT // SixteenBits
DXGI_FORMAT_R32_UINT // ThirtyTwoBits
```

```cpp
DXGI_FORMAT indexElementSize = DXGI_FORMAT_R16_UINT;
deviceContext->IASetIndexBuffer(indexBuffer, indexElementSize, 0);
```

**OpenGL 4**

```
GL_UNSIGNED_SHORT // SixteenBits
GL_UNSIGNED_INT   // ThirtyTwoBits
```

**Metal**

:pencil2:

### Primitive Topology

**Direct3D 11**

Use `enum D3D11_PRIMITIVE_TOPOLOGY` ([MSDN](https://msdn.microsoft.com/en-us/library/windows/desktop/ff476189.aspx)) in Direct3D 11:
```cpp
D3D11_PRIMITIVE_TOPOLOGY_POINTLIST     // PointList
D3D11_PRIMITIVE_TOPOLOGY_LINELIST      // LineList
D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP     // LineStrip
D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST  // TriangleList
D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP // TriangleStrip
```

usage in Direct3D 11:
```cpp
D3D11_PRIMITIVE_TOPOLOGY primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
deviceContext->IASetPrimitiveTopology(primitiveTopology);
```

**OpenGL 4**

Use `GLenum` ([Reference](https://www.opengl.org/sdk/docs/man/html/glDrawArrays.xhtml)) in OpenGL 4:

```cpp
GL_POINTS         // PointList
GL_LINES          // LineList
GL_LINE_STRIP     // LineStrip
GL_TRIANGLES      // TriangleList
GL_TRIANGLE_STRIP // TriangleStrip
```

usage in OpenGL 4:

```
GLenum primitiveTopology = GL_TRIANGLES;
```

**Metal**

Use `enum MTLPrimitiveType` ([Reference](https://developer.apple.com/library/prerelease/ios/documentation/Metal/Reference/MTLRenderCommandEncoder_Ref/index.html#//apple_ref/c/tdef/MTLPrimitiveType)) in Direct3D 11:

```objective-c
MTLPrimitiveTypePoint         // PointList
MTLPrimitiveTypeLine          // LineList
MTLPrimitiveTypeLineStrip     // LineStrip
MTLPrimitiveTypeTriangle      // TriangleList
MTLPrimitiveTypeTriangleStrip // TriangleStrip
```
usage in Metal:

```objective-c
MTLPrimitiveType primitiveTopology = MTLPrimitiveTypeTriangle;
```

### Viewport

**Direct3D 11**

:pencil2:

**OpenGL 4**

```cpp
struct {int X, Y, Width, Height; float MinDepth, MaxDepth} viewport;

glViewport(viewport.X, viewport.Y, viewport.Width, viewport.Height);
glDepthRangef(viewport.MinDepth, viewport.MaxDepth);
```

**Metal**

:pencil2:

### Scissor Rectangle

**Direct3D 11**

:pencil2:

**OpenGL 4**

```cpp
// Get scissor rectangle
std::array<GLint, 4> scissorBox;
glGetIntegerv(GL_SCISSOR_BOX, scissorBox.data());

struct {int X, Y, Width, Height} rectangle;
rectangle.X = scissorBox[0];
rectangle.Y = scissorBox[1];
rectangle.Width = scissorBox[2];
rectangle.Height = scissorBox[3];

// Set scissor rectangle
glScissor(rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height);
```

**Metal**

:pencil2:

----

## Pipeline State

### InputLayout

|Direct3D 11|Metal|
|:----------|:----|
|enum D3D11_INPUT_CLASSIFICATION|enum MTLVertexStepFunction|
|D3D11_INPUT_PER_VERTEX_DATA    |MTLVertexStepFunctionPerVertex|
|D3D11_INPUT_PER_INSTANCE_DATA  |MTLVertexStepFunctionPerInstance|
|--                             |MTLVertexStepFunctionConstant|

**Metal**

```objective-c
MTLVertexDescriptor* vertexDescriptor = [[MTLVertexDescriptor alloc] init];
vertexDescriptor.attributes[0].offset = 0;
vertexDescriptor.attributes[0].format = MTLVertexFormatFloat4;
vertexDescriptor.attributes[0].bufferIndex = 0;
vertexDescriptor.attributes[1].offset = sizeof(Float32) * 4;
vertexDescriptor.attributes[1].format = MTLVertexFormatFloat4;
vertexDescriptor.attributes[1].bufferIndex = 0;

vertexDescriptor.layouts[0].stride = 8 * sizeof(float);
vertexDescriptor.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
//vertexDescriptor.layouts[0].stepRate = 1;

MTLRenderPipelineDescriptor* pipelineDesc = [[MTLRenderPipelineDescriptor alloc] init];
pipelineDesc.vertexDescriptor = vertexDescriptot;
```

#### Step Rate

**OpenGL 4**

```cpp
glVertexAttribDivisor(attribute.StartSlot, 1);
```

**Direct3D 11**

```cpp
D3D11_INPUT_ELEMENT_DESC elementDesc;
elementDesc.InstanceDataStepRate = 1;
```

**Metal**

```objective-c
MTLVertexDescriptor* vertexDescriptor = [[MTLVertexDescriptor alloc] init];
vertexDescriptor.layouts[0].stepRate = 0;
```

----

## Shaders

### Create and Compile Shader

|Direct3D 11|OpenGL 4|Metal|
|:----------|:-------|:----|
|ID3D11VertexShader|GLuint, GL_VERTEX_SHADER|MTLFunction, MTLFunctionTypeVertex|
|ID3D11PixelShader|GLuint, GL_FRAGMENT_SHADER|MTLFunction, MTLFunctionTypeFragment|

**OpenGL 4**

```cpp
GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
```

**Metal**

```objective-c
id <MTLFunction> vertexProgram = [_defaultLibrary newFunctionWithName:@"lighting_vertex"];
id <MTLFunction> fragmentProgram = [_defaultLibrary newFunctionWithName:@"lighting_fragment"];
```

```objective-c
MTLCompileOptions* compileOptions = [[MTLCompileOptions alloc] init];
compileOptions.preprocessorMacros = @{@"DEBUG": @"1"};
NSError* compileError = nil;
NSString* shaderCode = @"...";
id<MTLLibrary> shaderLibrary = [_device newLibraryWithSource:shaderCode options:compileOptions error:&compileError];

id <MTLFunction> vertexProgram = [shaderLibrary newFunctionWithName:@"lighting_vertex"];
id <MTLFunction> fragmentProgram = [shaderLibrary newFunctionWithName:@"lighting_fragment"];
```

### Shader Language

:pencil2:

----

## Render States

:pencil2:

### Blend

:pencil2:

#### Blend Function

**Direct3D 11**

```cpp
D3D11_BLEND_OP_ADD          // Add
D3D11_BLEND_OP_SUBTRACT     // Subtract
D3D11_BLEND_OP_REV_SUBTRACT // ReverseSubtract
D3D11_BLEND_OP_MIN          // Min
D3D11_BLEND_OP_MAX          // Max
```

```cpp
D3D11_BLEND_OP blendFunction = D3D11_BLEND_OP_ADD;
```

**OpenGL 4**

:pencil2:

**Metal**

:pencil2:

#### Blend Factor

**Direct3D 11**

```cpp
D3D11_BLEND_ZERO             // Zero
D3D11_BLEND_ONE              // One
D3D11_BLEND_SRC_COLOR        // SourceColor
D3D11_BLEND_INV_SRC_COLOR    // InverseSourceColor
D3D11_BLEND_SRC_ALPHA        // SourceAlpha
D3D11_BLEND_INV_SRC_ALPHA    // InverseSourceAlpha
D3D11_BLEND_DEST_ALPHA       // DestinationAlpha
D3D11_BLEND_INV_DEST_ALPHA   // InverseDestinationAlpha
D3D11_BLEND_DEST_COLOR       // DestinationColor
D3D11_BLEND_INV_DEST_COLOR   // InverseDestinationColor
D3D11_BLEND_SRC_ALPHA_SAT    // SourceAlphaSaturation
D3D11_BLEND_BLEND_FACTOR     // BlendFactor
D3D11_BLEND_INV_BLEND_FACTOR // InvereseBlendFactor
```

```cpp
D3D11_BLEND blendFactor = D3D11_BLEND_ZERO;
```

**OpenGL 4**

:pencil2:

**Metal**

:pencil2:

### Depth Stencil

:pencil2:

#### Comparison Function

:pencil2:

#### Stencil Operation

:pencil2:

#### Stencil Operation

:pencil2:

### Rasterizer

**Direct3D 11**

Create Rasterizer State:

```cpp
D3D11_RASTERIZER_DESC rasterizerDesc;
rasterizerDesc.CullMode = description.CullMode;
rasterizerDesc.FillMode = description.FillMode;
rasterizerDesc.FrontCounterClockwise = FALSE;
rasterizerDesc.DepthBias = description.DepthBias;
rasterizerDesc.DepthBiasClamp = 0.0f;
rasterizerDesc.SlopeScaledDepthBias = description.SlopeScaledDepthBias;
rasterizerDesc.AntialiasedLineEnable = FALSE;
rasterizerDesc.MultisampleEnable = description.MultisampleEnable;
rasterizerDesc.ScissorEnable = TRUE;

HRESULT hr = device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
```

Apply Rasterizer State:

```cpp
Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState
deviceContext->RSSetState(rasterizerState.Get());
```

**OpenGL 4**

:pencil2:

**Metal**

:pencil2:

#### Cull Mode

:pencil2:

#### Fill Mode

**Direct3D 11**

```cpp
D3D11_FILL_SOLID     // Solid
D3D11_FILL_WIREFRAME // WireFrame
```

```cpp
D3D11_FILL_MODE fillMode = D3D11_FILL_SOLID;
rasterizerDesc.FillMode = fillMode;
```

**OpenGL 4**

```cpp
GL_FILL // Solid
GL_LINE // WireFrame
```

```cpp
GLenum fillMode = GL_FILL;
glPolygonMode(GL_FRONT_AND_BACK, fillMode.value);
```

**Metal**

:pencil2:

#### Scissor Test

**Direct3D 11**

```cpp
bool scissorTestEnable;
rasterizerDesc.ScissorEnable = (scissorTestEnable ? TRUE: FALSE);
```

**OpenGL 4**

```cpp
bool scissorTestEnable;

if (scissorTestEnable) {
  glEnable(GL_SCISSOR_TEST);
} else {
  glDisable(GL_SCISSOR_TEST);
}
```

**Metal**

:pencil2:

### Sampler

#### Create Sampler

**Direct3D 11**

```cpp
struct {
  D3D11_FILTER Filter;
  D3D11_TEXTURE_ADDRESS_MODE AddressU, AddressV, AddressW;
  float MinMipLevel, MaxMipLevel, MipMapLevelOfDetailBias;
  std::uint32_t MaxAnisotropy;
} description;

D3D11_SAMPLER_DESC samplerDesc;

// See "Texture Address Mode" section
samplerDesc.AddressU = description.AddressU;
samplerDesc.AddressV = description.AddressV;
samplerDesc.AddressW = description.AddressW;

// See "Texture Filter" section
samplerDesc.Filter = description.Filter;

samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
samplerDesc.MinLOD = description.MinMipLevel;
samplerDesc.MaxLOD = description.MaxMipLevel;
samplerDesc.MipLODBias = description.MipMapLevelOfDetailBias;
samplerDesc.MaxAnisotropy = description.MaxAnisotropy;

Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;

// Create Sampler State
HRESULT hr = device->CreateSamplerState(&samplerDesc, &samplerState);
```

**OpenGL**

```cpp
GLuint sampler = 0;

// Create Sampler
glGenSamplers(1, sampler);

// See "Texture Address Mode" section
glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, description.AddressU);
glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, description.AddressV);
glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R, description.AddressW);

// See "Texture Filter" section
glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// Set LOD
glSamplerParameterf(sampler, GL_TEXTURE_MIN_LOD, description.MaxMipLevel);
glSamplerParameterf(sampler, GL_TEXTURE_MAX_LOD, description.MaxMipLevel);
glSamplerParameterf(sampler, GL_TEXTURE_LOD_BIAS, description.MipMapLevelOfDetailBias);
```

**Metal**

:pencil2:

#### Apply Sampler

**Direct3D 11**

```cpp
UINT index = 0;
Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState = ...;
std::array<ID3D11SamplerState*, 1> const states = { samplerState.Get() };

deviceContext->PSSetSamplers(index, states.size(), states.data());
```

**OpenGL 4**

```cpp
GLuint index = 0;
GLuint sampler = ...;
glBindSampler(index, sampler);
```

**Metal**

:pencil2:

#### Texture Address Mode

**Direct3D 11**

```cpp
D3D11_TEXTURE_ADDRESS_CLAMP  // Clamp
D3D11_TEXTURE_ADDRESS_MIRROR // Mirror
D3D11_TEXTURE_ADDRESS_WRAP   // Wrap

D3D11_TEXTURE_ADDRESS_MODE textureAddressMode = D3D11_TEXTURE_ADDRESS_CLAMP;
```

**OpenGL 4**

```cpp
GL_CLAMP_TO_EDGE    // Clamp
GL_MIRRORED_REPEAT  // Mirror
GL_REPEAT           // Wrap

GLint textureAddressMode = GL_CLAMP_TO_EDGE;
```

**Metal**

:pencil2:

#### Texture Filter

**Direct3D 11**

```cpp
D3D11_FILTER_MIN_MAG_MIP_LINEAR              // Linear
D3D11_FILTER_MIN_MAG_MIP_POINT               // Point
D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT        // LinearMipPoint
D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR        // PointMipLinear
D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR // MinLinearMagPointMipLinear
D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT        // MinLinearMagPointMipPoint
D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR        // MinPointMagLinearMipLinear
D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT  // MinPointMagLinearMipPoint
D3D11_FILTER_ANISOTROPIC                     // Anisotropic
```

usage:

```cpp
D3D11_FILTER textureFilter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
```

**OpenGL 4**

Linear and point filtering:

```cpp
// TextureFilter::Linear
glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// TextureFilter::Point
glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

// TextureFilter::LinearMipPoint
glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// TextureFilter::PointMipLinear
glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

// TextureFilter::MinLinearMagPointMipLinear
glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

// TextureFilter::MinLinearMagPointMipPoint
glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

// TextureFilter::MinPointMagLinearMipLinear
glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// TextureFilter::MinPointMagLinearMipPoint
glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

Anisotropic filtering:

```cpp
// TextureFilter::Anisotropic
glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

GLfloat deviceMaxAnisotropy = 1.0f;
glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &deviceMaxAnisotropy);

deviceMaxAnisotropy = std::min(deviceMaxAnisotropy, static_cast<GLfloat>(description.MaxAnisotropy));

glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, deviceMaxAnisotropy);
```

**Metal**

:pencil2:

----

## Buffers

:pencil2:

### Create Constant Buffer

:pencil2:

### Create Index Buffer

:pencil2:

### Create Vertex Buffer

:pencil2:

### Dynamic Buffer

:pencil2:

----

## Textures

:pencil2:

### Texture 1D

:pencil2:

### Texture 2D

:pencil2:

### Texture 3D

:pencil2:

----

## Render Target

:pencil2:

----

## Pixel Format

:pencil2:

### Surface Format

:pencil2:

### Depth Format

:pencil2:
