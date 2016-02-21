## Texture Address Mode

- **D3D11_TEXTURE_ADDRESS_MODE** `DirectX 11` [:blue_book:]()
  ```cpp
  D3D11_TEXTURE_ADDRESS_CLAMP  // Clamp
  D3D11_TEXTURE_ADDRESS_MIRROR // Mirror
  D3D11_TEXTURE_ADDRESS_WRAP   // Wrap
  ```

- **D3D12_TEXTURE_ADDRESS_MODE** `DirectX 12` [:blue_book:]()
  ```cpp
  D3D12_TEXTURE_ADDRESS_MODE_CLAMP  // Clamp
  D3D12_TEXTURE_ADDRESS_MODE_MIRROR // Mirror
  D3D12_TEXTURE_ADDRESS_MODE_WRAP   // Wrap
  ```

- **GLint** `OpenGL` [:bookmark:]()
  ```cpp
  GL_CLAMP_TO_EDGE    // Clamp
  GL_MIRRORED_REPEAT  // Mirror
  GL_REPEAT           // Wrap
  ```

- **MTLSamplerAddressMode** `Metal` [:rocket:]()
```cpp
MTLSamplerAddressModeClampToEdge  // Clamp
MTLSamplerAddressModeMirrorRepeat // Mirror
MTLSamplerAddressModeRepeat       // Wrap
```

- **VkSamplerAddressMode** `Vulkan` [:volcano:]()
```cpp
VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE   // Clamp
VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT // Mirror
VK_SAMPLER_ADDRESS_MODE_REPEAT          // Wrap
```
