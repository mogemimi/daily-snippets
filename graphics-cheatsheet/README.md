### Words

| Direct3D 11                   | XNA 4.0                | OpenGL 4                       | Metal            | Vulkan |
|:------------------------------|:-----------------------|:-------------------------------|:-----------------|:-------|
| _DESC                         | --                     | --                             | Descriptor       | Info   |
| VertexShader                  | VertexShader           | VertexShader                   | VertexFunction   |        |
| PixelShader                   | PixelShader            | FragmentShader                 | FragmentFunction |        |
| InputLayout                   | VertexBufferBinding(s) | VertexArray & VertexAttributes | VertexLayout     |        |
| StepRate                      | InstanceFrequency      | VertexAttribDivisor            | StepRate         |        |
| ?                             | RenderTarget           | Framebuffer                    | ?                |        |
| BLEND_OP (Blending Operation) | BlendFunction          | ?                              | ?                |        |
| BLEND (Blend Factor)          | Blend                  | ?                              | ?                |        |

### Blend Function

| aa        | aa |
|:----------|:---|
| ```aaa``` |    |

### Blend Factor

### Shaders

| Direct3D 11          | OpenGL 4                       | Metal                                    | Vulkan |
|:---------------------|:-------------------------------|:-----------------------------------------|:-------|
| `ID3D11VertexShader` | `GLuint`, `GL_VERTEX_SHADER`   | `MTLFunction`, `MTLFunctionTypeVertex`   |        |
| `ID3D11PixelShader`  | `GLuint`, `GL_FRAGMENT_SHADER` | `MTLFunction`, `MTLFunctionTypeFragment` |        |







## Types and Classes

| General              | Direct3D 11                | Direct3D 12                | Metal                 | Vulkan            |
|:---------------------|:---------------------------|:---------------------------|:----------------------|:------------------|
| Input Classification | D3D11_INPUT_CLASSIFICATION | D3D12_INPUT_CLASSIFICATION | MTLVertexStepFunction | VkVertexInputRate |
| Input Classification | D3D11_INPUT_CLASSIFICATION | D3D12_INPUT_CLASSIFICATION | MTLVertexStepFunction | VkVertexInputRate |
