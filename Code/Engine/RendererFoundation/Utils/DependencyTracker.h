#pragma once

#include <RendererFoundation/RendererFoundationDLL.h>

template <typename Resource, typename Dependency>
class EZ_RENDERERFOUNDATION_DLL ezDependencyTracker
{
public:
  ezDependencyTracker();
  ~ezDependencyTracker();

  void AddResource(Resource* pResource, const ezSet<const Dependency*>& dependencies);
  void RemoveResource(Resource* pResource);
  void DependencyDestroyed(Dependency* pDependency);

public:
  ezEvent<Resource*> m_ResourceInvalidatedEvent;

private:
  struct Item
  {
    EZ_DECLARE_POD_TYPE();
    Item* m_pPreviousResource = nullptr;
    Item* m_pNextResource = nullptr;
    Item* m_pPreviousDependency = nullptr;
    Item* m_pNextDependency = nullptr;
    Resource* m_pResource = nullptr;
    const Dependency* m_pDependency = nullptr;
  };
  using ResourceHeadMap = ezMap<Resource*, Item*>;
  using DependencyHeadMap = ezMap<const Dependency*, Item*>;

private:
  void InsertItem(typename ResourceHeadMap::Iterator resourceHead, Resource* pResource, const Dependency* pDependency);
  void RemoveResourceItem(typename ResourceHeadMap::ConstIterator resourceHead, Item* pItem);
  void RemoveDependencyItem(typename DependencyHeadMap::ConstIterator dependencyHead, Item* pItem);

private:
  ezMutex m_Mutex;
  ezDeque<Item> m_Dependencies;
  Item* m_pFreeList = nullptr;
  ResourceHeadMap m_ResourceHead;
  DependencyHeadMap m_DependencyHead;
};

#include <RendererFoundation/Utils/Implementation/DependencyTracker_inl.h>
