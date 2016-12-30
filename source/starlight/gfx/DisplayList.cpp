#include "DisplayList.h"

#include "starlight/gfx/RenderCore.h"

using starlight::gfx::RenderCore;

using starlight::gfx::DLNodeType;

using starlight::gfx::DLNode;
using starlight::gfx::DLNode_Quads;
using starlight::gfx::DisplayList;

void DisplayList::Run(Vector2 offset) {
    for (auto n : nodes) n->Apply(offset);
}

void DLNode_Quads::Apply(Vector2 offset) {
    for (auto r : rects) RenderCore::DrawQuad(r.first + offset, r.second);
}
void DisplayList::AddQuad(VRect& quad, VRect& uv) {
    auto node = (!nodes.empty() && nodes.back()->Type() == DLNodeType::Quads) ? std::static_pointer_cast<DLNode_Quads>(nodes.back()) : CreateNode<DLNode_Quads>();
    node->Add(quad, uv);
}

