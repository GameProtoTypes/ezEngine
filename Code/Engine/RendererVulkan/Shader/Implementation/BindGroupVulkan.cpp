#include <RendererVulkan/Shader/BindGroupVulkan.h>

// Implementation of ezGALBindGroupVulkan

ezGALBindGroupVulkan::ezGALBindGroupVulkan(const ezGALBindGroupCreationDescription& Description)
  : ezGALBindGroup(Description)
{
  // Vulkan-specific initialization can be added here
}

ezGALBindGroupVulkan::~ezGALBindGroupVulkan()
{
  // Vulkan-specific cleanup can be added here
}

ezResult ezGALBindGroupVulkan::InitPlatform(ezGALDevice* pDevice)
{
  // Vulkan-specific resource binding initialization
  return EZ_SUCCESS;
}

ezResult ezGALBindGroupVulkan::DeInitPlatform(ezGALDevice* pDevice)
{
  // Vulkan-specific resource binding cleanup
  return EZ_SUCCESS;
}

void ezGALBindGroupVulkan::Invalidate(ezGALDevice* pDevice)
{
  if (m_DescriptorSet != nullptr)
  {

    m_DescriptorSet = nullptr;
  }
}

bool ezGALBindGroupVulkan::IsInvalidated() const
{
  return m_DescriptorSet != nullptr;
}

void ezGALBindGroupVulkan::SetDebugNamePlatform(const char* szName) const
{
}
