#pragma once
#include "starlight/_global.h"

#include <string>

#include "starlight/ThemeManager.h"

namespace starlight {
    namespace gfx {
        template <class T>
        class ThemeRef {
            friend class starlight::ThemeManager;
        protected:
            const std::string name;
            T* ptr = nullptr;
            void Unload() {
                delete ptr;
                ptr = nullptr;
            }
            
            ThemeRef(std::string name, T* ptr) : name(name), ptr(ptr) { }
            ThemeRef(std::string name) : name(name) { }
        public:
            ~ThemeRef() { }
            
            ThemeRef<T>& operator ++() { return *this; }
            T* operator ->() {
                if (ptr == nullptr) {
                    ThemeManager::Fulfill(*this); // call thememanager to grab things
                }
                return ptr;
            }
            
        };
    }
}
