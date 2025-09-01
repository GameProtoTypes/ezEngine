#pragma once

#include <GuiFoundation/PropertyGrid/Implementation/PropertyWidget.moc.h>
#include <VisualScriptPlugin/Runtime/VisualScriptDataType.h>

struct ezVisualScriptVariableType
{
  using StorageType = ezUInt8;

  enum Enum
  {
    Bool = ezVisualScriptDataType::Bool,
    Byte,
    Int,
    Int64,
    Float,
    Double,
    Color,
    Vector3,
    Quaternion,
    Transform,
    Time,
    Angle,
    String,
    HashedString,
    GameObject,
    Component,
    TypedPointer,
    Variant,

    Resource = ezVisualScriptDataType::Resource,

    Default = Int,
  };
};

EZ_DECLARE_REFLECTABLE_TYPE(EZ_EDITORPLUGINVISUALSCRIPT_DLL, ezVisualScriptVariableType);

//////////////////////////////////////////////////////////////////////////////

struct ezVisualScriptVariableCategory
{
  using StorageType = ezUInt8;

  enum Enum
  {
    Member,
    Array,
    Map,
    Default = Member,
  };

  static ezPropertyCategory::Enum GetPropertyCategory(Enum category);
};

EZ_DECLARE_REFLECTABLE_TYPE(EZ_EDITORPLUGINVISUALSCRIPT_DLL, ezVisualScriptVariableCategory);

//////////////////////////////////////////////////////////////////////////////

struct ezVisualScriptVariable
{
  ezHashedString m_sName;
  ezVariant m_DefaultValue;
  ezEnum<ezVisualScriptVariableType> m_Type;
  ezEnum<ezVisualScriptVariableCategory> m_Category;
  bool m_bExpose = false;

  void SetType(ezVisualScriptVariableType::Enum type);
  ezVisualScriptVariableType::Enum GetType() const { return m_Type; }

  void SetCategory(ezVisualScriptVariableCategory::Enum category);
  ezVisualScriptVariableCategory::Enum GetCategory() const { return m_Category; }
};

EZ_DECLARE_REFLECTABLE_TYPE(EZ_EDITORPLUGINVISUALSCRIPT_DLL, ezVisualScriptVariable);

//////////////////////////////////////////////////////////////////////////

class ezVisualScriptVariableAttribute : public ezTypeWidgetAttribute
{
  EZ_ADD_DYNAMIC_REFLECTION(ezVisualScriptVariableAttribute, ezTypeWidgetAttribute);
};

//////////////////////////////////////////////////////////////////////////

class ezQtVisualScriptVariableWidget : public ezQtVariantPropertyWidget
{
  Q_OBJECT;

public:
  ezQtVisualScriptVariableWidget();
  virtual ~ezQtVisualScriptVariableWidget();
};

//////////////////////////////////////////////////////////////////////////

struct ezVisualScriptExpressionDataType
{
  using StorageType = ezUInt8;

  enum Enum
  {
    Int = static_cast<ezUInt8>(ezProcessingStream::DataType::Int),
    Float = static_cast<ezUInt8>(ezProcessingStream::DataType::Float),
    Vector3 = static_cast<ezUInt8>(ezProcessingStream::DataType::Float3),
    Color = static_cast<ezUInt8>(ezProcessingStream::DataType::Float4),

    Default = Float
  };

  static ezVisualScriptDataType::Enum GetVisualScriptDataType(Enum dataType);
};

EZ_DECLARE_REFLECTABLE_TYPE(EZ_EDITORPLUGINVISUALSCRIPT_DLL, ezVisualScriptExpressionDataType);

struct ezVisualScriptExpressionVariable
{
  ezHashedString m_sName;
  ezEnum<ezVisualScriptExpressionDataType> m_Type;
};

EZ_DECLARE_REFLECTABLE_TYPE(EZ_EDITORPLUGINVISUALSCRIPT_DLL, ezVisualScriptExpressionVariable);
