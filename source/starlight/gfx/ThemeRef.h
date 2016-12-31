#pragma once
#include "starlight/_global.h"

#include <string>

#include "starlight/ThemeManager.h"

namespace starlight {
    namespace gfx {
        template <class T>
        class ThemeRefContainer {
            friend class starlight::ThemeManager;
        protected:
            const std::string name;
            T* ptr = nullptr;
            void Unload() {
                delete ptr;
                ptr = nullptr;
            }
            
            ThemeRefContainer(std::string name, T* ptr) : name(name), ptr(ptr) { }
            ThemeRefContainer(std::string name) : name(name) { }
        public:
            ~ThemeRefContainer() { }
            
            T* operator ->() const {
                if (ptr == nullptr) {
                    ThemeManager::Fulfill(const_cast<ThemeRefContainer<T>&>(*this)); // call thememanager to grab things
                }
                return ptr;
            }
            
            /*T& operator *() const {
                if (ptr == nullptr) {
                    ThemeManager::Fulfill(const_cast<ThemeRef<T>&>(*this)); // call thememanager to grab things
                }
                return *ptr;
            }*/
            
        };
        
        template <class T>
        class ThemeRef {
        private:
            const ThemeRefContainer<T>* cptr;
        public:
            ThemeRef() : cptr(nullptr) { }
            ThemeRef(ThemeRefContainer<T>* c) : cptr(c) { }
            ~ThemeRef() { }
            inline const ThemeRefContainer<T>& operator ->() const { return *cptr; }
            inline explicit operator bool() const { return cptr != nullptr; }
        };
    }
}
