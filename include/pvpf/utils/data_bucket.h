//
// Created by Jiabei He on 23/06/2018.
//

#ifndef DEV_ENV_DATA_BUCKET_H
#define DEV_ENV_DATA_BUCKET_H
#pragma once

#include <core/any.hpp>
#include <map>
#include "pvpf/pvpf.h"

PVPF_NAMESPACE_BEGIN

    class data_bucket {
    private:
        std::map<std::string, std::shared_ptr<core::any>> *map;
    public:
        data_bucket() {
            map = new std::map<std::string, std::shared_ptr<core::any>>();
        }

        ~data_bucket() {
            delete map;
        }

        data_bucket(const data_bucket &new_data_bucket) = delete;

        data_bucket(data_bucket &&new_data_bucket) noexcept : map(new_data_bucket.map) {
            new_data_bucket.map = nullptr;
        }

        data_bucket &operator=(data_bucket &&new_data_bucket) noexcept {
            if (this != &new_data_bucket) {
                map = new_data_bucket.map;
                new_data_bucket.map = nullptr;
            }

            return *this;
        }

        template<typename T>
        void put(std::string const &key, T &&value) {
            (*map)[key] = std::make_shared<core::any>(std::forward<T>(value));
        }

        template<typename T>
        T get_copy(std::string const &key) {
            if (!(map->count(key))) throw std::logic_error(std::string("key:") + key + std::string(" does not exist"));

            std::weak_ptr<core::any> ptr = (*map)[key];
            if (auto spt = ptr.lock()) {
                return core::any_cast<T>(*spt);
            } else {
                throw std::logic_error(std::string("key:") + key + std::string(" does not exist"));
            }
        }

        template<typename T>
        T *get_ptr(std::string const &key) {
            if (!(map->count(key))) throw std::logic_error(std::string("key:") + key + std::string(" does not exist"));

            std::weak_ptr<core::any> ptr = (*map)[key];
            if (auto spt = ptr.lock()) {
                T *ptr = core::any_cast<T>(spt.get());
                return ptr;
            } else {
                throw std::logic_error(std::string("key:") + key + std::string(" does not exist"));
            }
        }

        unsigned long size() {
            return this->map ? this->map->size() : 0;
        }

        std::map<std::string, std::shared_ptr<core::any>>::iterator begin() {
            return this->map->begin();
        }

        std::map<std::string, std::shared_ptr<core::any>>::iterator end() {
            return this->map->end();
        }
    };

PVPF_NAMESPACE_END

#endif //DEV_ENV_DATA_BUCKET_H