#pragma once
#include "idamagepolicy.hpp"
#include <memory>
#include <string>

class ResistanceDamagePolicy : public IDamagePolicy
{
public:
    int ModifyDamage(int rawDamage) const override
    {
        return rawDamage / 2;
    }

    std::string GetPolicyName() const override
    {
        return "Сопротивление (x0.5)";
    }

    std::unique_ptr<IDamagePolicy> Clone() const override
    {
        return std::make_unique<ResistanceDamagePolicy>(*this);
    }
};