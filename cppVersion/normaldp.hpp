#pragma once
#include "idamagepolicy.hpp"
#include <memory>

class NormalDamagePolicy : public IDamagePolicy
{
public:
    int ModifyDamage(int rawDamage) const override
    {
        return rawDamage;
    }

    std::string GetPolicyName() const override
    {
        return "Обычный урон (x1)";
    }

    std::unique_ptr<IDamagePolicy> Clone() const override
    {
        return std::make_unique<NormalDamagePolicy>(*this);
    }
};