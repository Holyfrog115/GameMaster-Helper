#pragma once
#include <memory>
#include <string>

class IDamagePolicy
{
public:
    virtual ~IDamagePolicy() noexcept = default;

    virtual int ModifyDamage(int rawDamage) const        = 0;
    virtual std::string GetPolicyName() const            = 0;
    virtual std::unique_ptr<IDamagePolicy> Clone() const = 0;
};