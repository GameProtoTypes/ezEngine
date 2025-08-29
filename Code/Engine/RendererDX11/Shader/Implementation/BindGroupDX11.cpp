#include <RendererDX11/Shader/BindGroupDX11.h>

// Implementation of ezGALBindGroupDX11

ezGALBindGroupDX11::ezGALBindGroupDX11(const ezGALBindGroupCreationDescription& Description)
  : ezGALBindGroup(Description)
{
  // DX11-specific initialization can be added here
}

ezGALBindGroupDX11::~ezGALBindGroupDX11()
{
  // DX11-specific cleanup can be added here
}

ezResult ezGALBindGroupDX11::InitPlatform(ezGALDevice* pDevice)
{
  // DX11-specific resource binding initialization
  return EZ_SUCCESS;
}

ezResult ezGALBindGroupDX11::DeInitPlatform(ezGALDevice* pDevice)
{
  // DX11-specific resource binding cleanup
  return EZ_SUCCESS;
}

void ezGALBindGroupDX11::Invalidate(ezGALDevice* pDevice)
{
  m_bInvalidated = true;
}

bool ezGALBindGroupDX11::IsInvalidated() const
{
  return m_bInvalidated;
}

void ezGALBindGroupDX11::SetDebugNamePlatform(const char* szName) const
{
}
