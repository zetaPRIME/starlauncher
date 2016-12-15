#pragma once
#include "starlight/_global.h"

#include <memory>
#include <3ds.h>
#include <citro3d.h>

namespace starlight {
    namespace gfx {
        class RenderCore;
        
        class CTexture {
        protected:
            CTexture() = default;
            
        public:
            virtual ~CTexture() = default;
            virtual void Bind(Color color = Color::white) = 0;
        };
        
        class CRenderTarget : public CTexture {
            friend class starlight::gfx::RenderCore;
        protected:
            C3D_RenderTarget* tgt;
            
        public:
            C3D_Mtx projection;
            
            CRenderTarget(int width, int height);
            ~CRenderTarget();
            
            void BindTarget();
            
            void Bind(Color color = Color::white) override;
        };
        
        class RenderCore {
        public:
            static std::unique_ptr<CRenderTarget> targetTopLeft;
            static std::unique_ptr<CRenderTarget> targetTopRight;
            static std::unique_ptr<CRenderTarget> targetBottom;
            
            RenderCore() = delete; // static
            
            static void Open();
            static void Close();
            
            static void BeginFrame();
            static void EndFrame();
            
            static void BindTexture(C3D_Tex* tex, const Color& color);
            static void BindColor(const Color& color);
            static void DrawQuad(VRect rect, VRect src);
        };
    }
}
