#include <EditorPluginVisualScript/EditorPluginVisualScriptPCH.h>

#include <EditorPluginVisualScript/VisualScriptGraph/VisualScriptVariable.moc.h>

#include <Foundation/Serialization/AbstractObjectGraph.h>
#include <Foundation/Serialization/GraphPatch.h>
#include <GuiFoundation/PropertyGrid/PropertyGridWidget.moc.h>
#include <ToolsFoundation/Object/ObjectAccessorBase.h>

// clang-format off
EZ_BEGIN_STATIC_REFLECTED_ENUM(ezVisualScriptVariableType, 1)
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Bool),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Byte),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Int),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Int64),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Float),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Double),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Color),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Vector3),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Quaternion),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Transform),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Time),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Angle),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::String),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::HashedString),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::GameObject),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Component),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::TypedPointer),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Variant),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableType::Resource),
EZ_END_STATIC_REFLECTED_ENUM;
// clang-format on

static_assert(ezVisualScriptVariableType::Variant == ezVisualScriptDataType::Variant);
static_assert(ezVisualScriptVariableType::Resource == ezVisualScriptDataType::Resource);

///////////////////////////////////////////////////////////////////////////

// clang-format off
EZ_BEGIN_STATIC_REFLECTED_ENUM(ezVisualScriptVariableCategory, 1)
  EZ_ENUM_CONSTANT(ezVisualScriptVariableCategory::Member),
  EZ_ENUM_CONSTANT(ezVisualScriptVariableCategory::Array),
  //EZ_ENUM_CONSTANT(ezVisualScriptVariableCategory::Map), // Maps are not supported yet
EZ_END_STATIC_REFLECTED_ENUM;
// clang-format on

// static
ezPropertyCategory::Enum ezVisualScriptVariableCategory::GetPropertyCategory(Enum category)
{
  switch (category)
  {
    case Member:
      return ezPropertyCategory::Member;
    case Array:
      return ezPropertyCategory::Array;
    case Map:
      return ezPropertyCategory::Map;
    default:
      EZ_ASSERT_NOT_IMPLEMENTED;
      return ezPropertyCategory::Member;
  }
}

///////////////////////////////////////////////////////////////////////////

// clang-format off
EZ_BEGIN_STATIC_REFLECTED_TYPE(ezVisualScriptVariable, ezNoBase, 2, ezRTTIDefaultAllocator<ezVisualScriptVariable>)
{
  EZ_BEGIN_PROPERTIES
  {
    EZ_MEMBER_PROPERTY("Name", m_sName),
    EZ_ENUM_ACCESSOR_PROPERTY("Type", ezVisualScriptVariableType, GetType, SetType),
    EZ_ENUM_ACCESSOR_PROPERTY("Category", ezVisualScriptVariableCategory, GetCategory, SetCategory),
    EZ_MEMBER_PROPERTY("DefaultValue", m_DefaultValue)->AddAttributes(new ezDefaultValueAttribute(0), new ezVisualScriptVariableAttribute()),
    EZ_MEMBER_PROPERTY("Expose", m_bExpose),
  }
  EZ_END_PROPERTIES;
}
EZ_END_STATIC_REFLECTED_TYPE;
// clang-format on

void ezVisualScriptVariable::SetType(ezVisualScriptVariableType::Enum type)
{
  if (m_Type == type)
    return;

  m_Type = type;

  // TODO
}

void ezVisualScriptVariable::SetCategory(ezVisualScriptVariableCategory::Enum category)
{
  if (m_Category == category)
    return;

  m_Category = category;

  // TODO
}

///////////////////////////////////////////////////////////////////////////

class ezVisualScriptVariablePatch_1_2 : public ezGraphPatch
{
public:
  ezVisualScriptVariablePatch_1_2()
    : ezGraphPatch("ezVisualScriptVariable", 2)
  {
  }

  virtual void Patch(ezGraphPatchContext& ref_context, ezAbstractObjectGraph* pGraph, ezAbstractObjectNode* pNode) const override
  {
    if (auto* pDefaultValue = pNode->FindProperty("DefaultValue"))
    {
      ezVariantType::Enum variantType = pDefaultValue->m_Value.GetType();
      ezInt64 dataType = ezVisualScriptDataType::FromVariantType(variantType);
      ezInt64 category = ezVisualScriptVariableCategory::Member;

      if (variantType == ezVariantType::VariantArray)
      {
        dataType = ezVisualScriptDataType::Variant;
        category = ezVisualScriptVariableCategory::Array;
      }
      else if (variantType == ezVariantType::VariantDictionary)
      {
        dataType = ezVisualScriptDataType::Variant;
        category = ezVisualScriptVariableCategory::Map;
      }

      pNode->AddProperty("Type", dataType);
      pNode->AddProperty("Category", category);
    }
  }
};

ezVisualScriptVariablePatch_1_2 g_ezVisualScriptVariablePatch_1_2;

//////////////////////////////////////////////////////////////////////////

// clang-format off
EZ_BEGIN_DYNAMIC_REFLECTED_TYPE(ezVisualScriptVariableAttribute, 1, ezRTTIDefaultAllocator<ezVisualScriptVariableAttribute>)
EZ_END_DYNAMIC_REFLECTED_TYPE;
// clang-format on

//////////////////////////////////////////////////////////////////////////

static ezQtPropertyWidget* VisualScriptVariableTypeCreator(const ezRTTI* pRtti)
{
  return new ezQtVisualScriptVariableWidget();
}

// clang-format off
EZ_BEGIN_SUBSYSTEM_DECLARATION(EditorPluginVisualScript, VisualScriptVariable)

  BEGIN_SUBSYSTEM_DEPENDENCIES
  "ToolsFoundation", "PropertyMetaState"
  END_SUBSYSTEM_DEPENDENCIES

  ON_CORESYSTEMS_STARTUP
  {
    ezQtPropertyGridWidget::GetFactory().RegisterCreator(ezGetStaticRTTI<ezVisualScriptVariableAttribute>(), VisualScriptVariableTypeCreator);
  }

  ON_CORESYSTEMS_SHUTDOWN
  {
    ezQtPropertyGridWidget::GetFactory().UnregisterCreator(ezGetStaticRTTI<ezVisualScriptVariableAttribute>());
  }

EZ_END_SUBSYSTEM_DECLARATION;
// clang-format on

ezQtVisualScriptVariableWidget::ezQtVisualScriptVariableWidget()
{
  EnableTypeSelection(false);
}

ezQtVisualScriptVariableWidget::~ezQtVisualScriptVariableWidget() = default;

//////////////////////////////////////////////////////////////////////////

// clang-format off
EZ_BEGIN_STATIC_REFLECTED_ENUM(ezVisualScriptExpressionDataType, 1)
  EZ_ENUM_CONSTANT(ezVisualScriptExpressionDataType::Int),
  EZ_ENUM_CONSTANT(ezVisualScriptExpressionDataType::Float),
  EZ_ENUM_CONSTANT(ezVisualScriptExpressionDataType::Vector3),
  EZ_ENUM_CONSTANT(ezVisualScriptExpressionDataType::Color),
EZ_END_STATIC_REFLECTED_ENUM;

EZ_BEGIN_STATIC_REFLECTED_TYPE(ezVisualScriptExpressionVariable, ezNoBase, 1, ezRTTIDefaultAllocator<ezVisualScriptExpressionVariable>)
{
  EZ_BEGIN_PROPERTIES
  {
    EZ_MEMBER_PROPERTY("Name", m_sName),
    EZ_ENUM_MEMBER_PROPERTY("Type", ezVisualScriptExpressionDataType, m_Type),
  }
  EZ_END_PROPERTIES;
}
EZ_END_STATIC_REFLECTED_TYPE;
// clang-format on

ezVisualScriptDataType::Enum ezVisualScriptExpressionDataType::GetVisualScriptDataType(Enum dataType)
{
  switch (dataType)
  {
    case Int:
      return ezVisualScriptDataType::Int;
    case Float:
      return ezVisualScriptDataType::Float;
    case Vector3:
      return ezVisualScriptDataType::Vector3;
    case Color:
      return ezVisualScriptDataType::Color;
    default:
      EZ_ASSERT_NOT_IMPLEMENTED;
  }

  return ezVisualScriptDataType::Invalid;
}
