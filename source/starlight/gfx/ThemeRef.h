#pragma once

#include <string>

#include "starlight/ThemeManager.h"

namespace starlight {
    namespace gfx {
        template <class T>
        class ThemeRef {
            friend class ThemeManager;
        protected:
            const std::string name;
            T* ptr = nullptr;
            void Unload() {
                delete ptr;
                ptr = nullptr;
            }
            
            ThemeRef(std::string name, T* ptr) : name(name), ptr(ptr) { }
        public:
            ~ThemeRef() { }
            
            ThemeRef<T>& operator ++() const { return *this; }
            T operator ->() const {
                if (ptr == nullptr) {
                    // call thememanager to grab things
                }
                return ptr;
            }
            
        };
    }
}
