#include "GFXManager.h"

using starlight::GFXManager;
using starlight::gfx::DrawContext;

std::forward_list<DrawContext*> GFXManager::ctxStack;

void GFXManager::PushContext(DrawContext* context) {
    if (!ctxStack.empty()) ctxStack.front()->Close();
    ctxStack.push_front(context);
    context->Open();
}

DrawContext* GFXManager::PopContext() {
    DrawContext* context = ctxStack.front();
    context->Close();
    ctxStack.pop_front();
    if (!ctxStack.empty()) ctxStack.front()->Open();
    return context;
}

DrawContext* GFXManager::GetContext() { return !ctxStack.empty() ? ctxStack.front() : nullptr; }

bool GFXManager::PrepareForDrawing() {
    if (ctxStack.empty()) return false;
    auto context = ctxStack.front();
    if (context->drawReady) return true;
    return context->Prepare();
}

