### Texture Filter

| API             | type                                         |
|:----------------|:---------------------------------------------|
| **Direct3D 11** | D3D11_FILTER                                 |
| **Direct3D 12** | D3D12_FILTER                                 |
| **OpenGL 4**    | GLint                                        |
| **Metal**       | MTLSamplerMinMagFilter + MTLSamplerMipFilter |
| **Vulkan**      | Vk                                           |

- D3D11_FILTER
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

- D3D12_FILTER
  ```cpp
  D3D12_FILTER_ANISOTROPIC
  D3D12_FILTER_MIN_MAG_MIP_LINEAR
  D3D12_FILTER_MIN_MAG_MIP_POINT
  D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT
  D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR
  D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR
  D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT
  D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR
  D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT
  ```

- OpenGL
  ```cpp
  // Linear
  glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Point
  glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // LinearMipPoint
  glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // PointMipLinear
  glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // MinLinearMagPointMipLinear
  glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // MinLinearMagPointMipPoint
  glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // MinPointMagLinearMipLinear
  glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // MinPointMagLinearMipPoint
  glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  ```

- MTL
  ```cpp
  MTLSamplerDescriptor* descriptor = [[MTLSamplerDescriptor alloc] init];

  // Anisotropic:
  descriptor.minFilter = MTLSamplerMinMagFilterLinear;
  descriptor.magFilter = MTLSamplerMinMagFilterLinear;
  descriptor.mipFilter = MTLSamplerMipFilterNotMipmapped;

  // Linear:
  descriptor.minFilter = MTLSamplerMinMagFilterLinear;
  descriptor.magFilter = MTLSamplerMinMagFilterLinear;
  descriptor.mipFilter = MTLSamplerMipFilterLinear;

  // Point:
  descriptor.minFilter = MTLSamplerMinMagFilterNearest;
  descriptor.magFilter = MTLSamplerMinMagFilterNearest;
  descriptor.mipFilter = MTLSamplerMipFilterNearest;

  // LinearMipPoint:
  descriptor.minFilter = MTLSamplerMinMagFilterLinear;
  descriptor.magFilter = MTLSamplerMinMagFilterLinear;
  descriptor.mipFilter = MTLSamplerMipFilterNearest;

  // PointMipLinear:
  descriptor.minFilter = MTLSamplerMinMagFilterNearest;
  descriptor.magFilter = MTLSamplerMinMagFilterNearest;
  descriptor.mipFilter = MTLSamplerMipFilterLinear;

  // MinLinearMagPointMipLinear:
  descriptor.minFilter = MTLSamplerMinMagFilterLinear;
  descriptor.magFilter = MTLSamplerMinMagFilterNearest;
  descriptor.mipFilter = MTLSamplerMipFilterLinear;

  // MinLinearMagPointMipPoint:
  descriptor.minFilter = MTLSamplerMinMagFilterLinear;
  descriptor.magFilter = MTLSamplerMinMagFilterNearest;
  descriptor.mipFilter = MTLSamplerMipFilterNearest;

  // MinPointMagLinearMipLinear:
  descriptor.minFilter = MTLSamplerMinMagFilterNearest;
  descriptor.magFilter = MTLSamplerMinMagFilterLinear;
  descriptor.mipFilter = MTLSamplerMipFilterLinear;

  // MinPointMagLinearMipPoint:
  descriptor.minFilter = MTLSamplerMinMagFilterNearest;
  descriptor.magFilter = MTLSamplerMinMagFilterLinear;
  descriptor.mipFilter = MTLSamplerMipFilterNearest;
  ```

- Vk
  ```cpp
  ```
  
