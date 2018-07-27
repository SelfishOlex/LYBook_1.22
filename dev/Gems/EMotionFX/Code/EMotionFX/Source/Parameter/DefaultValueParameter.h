/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

#include "ValueParameter.h"
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/SerializeContext.h>

namespace EMotionFX
{
    template <class ValueType, class Derived>
    class DefaultValueParameter
        : public ValueParameter
    {
    public:
        AZ_RTTI(((DefaultValueParameter<ValueType, Derived>), "{AE70C43D-6BAE-4EDF-A1CF-FC18B9F92ABB}", ValueType, Derived), ValueParameter);

        DefaultValueParameter(const ValueType& defaultValue)
            : m_defaultValue(defaultValue)
        {
        }

        static void Reflect(AZ::ReflectContext* context);

        ValueType GetDefaultValue() const { return m_defaultValue; }
        void SetDefaultValue(const ValueType& newValue) { m_defaultValue = newValue; }

    protected:
        ValueType m_defaultValue;
    };

    template <class ValueType, class Derived>
    void DefaultValueParameter<ValueType, Derived>::Reflect(AZ::ReflectContext* context)
    {
        using ThisType = DefaultValueParameter<ValueType, Derived>;

        AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context);
        if (!serializeContext)
        {
            return;
        }

        serializeContext->Class<ThisType, ValueParameter>()
            ->Version(1)
            ->Field("defaultValue", &ThisType::m_defaultValue)
        ;

        AZ::EditContext* editContext = serializeContext->GetEditContext();
        if (!editContext)
        {
            return;
        }

        editContext->Class<ThisType>("Non-range value parameter", "")
            ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
            ->DataElement(AZ::Edit::UIHandlers::Default, &ThisType::m_defaultValue, "Default", "Parameter's default value")
        ;
    }
}