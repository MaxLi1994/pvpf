//
// Created by Icay on 21/06/2018.
//

#ifndef VALIDATION_RULE_H
#define VALIDATION_RULE_H

#endif //VALIDATION_RULE_H
#pragma once

#include <iostream>
#include <rapidjson/document.h>
#include "pvpf/pvpf.h"
#include "config_validator.h"

PVPF_NAMESPACE_BEGIN

namespace config
{
    class validation_rule{
    public:
        virtual validation_result validate(rapidjson::Document &conf) = 0;
    };

    // check the JSON format
    class concrete_rule_format : public validation_rule {
    public:
        validation_result validate(rapidjson::Document &conf) override;
    };

    class concrete_rule_source : public validation_rule {
    public:
        validation_result validate(rapidjson::Document &conf) override;
    };

    class concrete_rule_graph : public validation_rule {
    public:
        validation_result validate(rapidjson::Document &conf) override;
    };

    class concrete_rule_sink : public validation_rule {
    public:
        validation_result validate(rapidjson::Document &conf) override;
    };

    class concrete_rule_duplicate_id : public validation_rule {
    public:
        validation_result validate(rapidjson::Document &conf) override;
    };

    //TODO
    class concrete_rule_library_search : public validation_rule {
    public:
        validation_result validate(rapidjson::Document &conf) override;
    };

    class concrete_rule_predecessor_check : public validation_rule {
    public:
        validation_result validate(rapidjson::Document &conf) override;
    };

    class concrete_rule_successor_check : public validation_rule {
    public:
        validation_result validate(rapidjson::Document &conf) override;
    };

}

PVPF_NAMESPACE_END