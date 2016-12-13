#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <cmath>

#include "FontSFTD.h"

using starlight::Vector2;
using starlight::VRect;
using starlight::gfx::Font;
using starlight::gfx::FontSFTD;

FontSFTD::~FontSFTD() {
    sftd_free_font(sfont);
}

#define err(nth, wat) *((unsigned int*)0x00100000+(nth))=wat;
#define ded(wat) err(0,wat)
Vector2 FontSFTD::Measure(std::string& text, int size, int maxWidth) {
    Vector2 v;
    PrintOp(Vector2(), text, size, Color(), Vector2(), nullptr, maxWidth, &v);
    return v;
}

void FontSFTD::Print(Vector2 position, std::string& text, int size, Color color, Vector2 justification, OptRef<Color> borderColor) {
    PrintOp(position, text, size, color, justification, borderColor, 2147483647, static_cast<Vector2*>(nullptr));
}

void FontSFTD::Print(VRect rect, std::string& text, int size, Color color, Vector2 justification, OptRef<Color> borderColor) {
    Vector2 pos = rect.pos + rect.size * justification;
    PrintOp(pos, text, size, color, justification, borderColor, rect.size.x, static_cast<Vector2*>(nullptr));
}

void FontSFTD::PrintOp(Vector2 position, std::string& text, int size, const Color& color, Vector2 justification, OptRef<Color> borderColor, int maxWidth, Vector2* measure) {
    int lineHeight = 0; int spaceWidth = 0;
    sftd_calc_bounding_box(&spaceWidth, &lineHeight, sfont, size, size*2, "Q");
    spaceWidth = sftd_get_text_width(sfont, size, " ");
    
    int longest = 0;
    std::vector<std::list<std::string>> ptree;
    std::vector<int> lwidth;
    {
        std::stringstream ss(text);
        std::string line, word;
        
        // prepare line buffer
        ptree.push_back(std::list<std::string>());
        auto* cline = &ptree.back();
        int cLineLen = -spaceWidth;
        
        // split into words and lines
        while(getline(ss, line, '\n')) {
            std::stringstream ls(line);
            while (getline(ls, word, ' ')) {
                int ww = spaceWidth + sftd_get_text_width(sfont, size, word.c_str());
                if (cLineLen + ww > maxWidth) {
                    lwidth.push_back(cLineLen);
                    ptree.push_back(std::list<std::string>());
                    cline = &ptree.back();
                    if (cLineLen > longest) longest = cLineLen;
                    cLineLen = -spaceWidth;
                }
                cLineLen += ww;
                cline->push_back(word);
                //
            }
            lwidth.push_back(cLineLen);
            ptree.push_back(std::list<std::string>());
            cline = &ptree.back();
            if (cLineLen > longest) longest = cLineLen;
            cLineLen = -spaceWidth;
        }
    }
    
    if (measure != nullptr) { // measurement operation
        *measure = Vector2(longest, lwidth.size() * lineHeight);
        return;
    }
    
    Vector2 lp = position - Vector2(0, lwidth.size() * lineHeight) * justification;
    lp.x = floor(lp.x); lp.y = floor(lp.y); // normalize across zero-crossings
    int li = 0;
    
    for (auto& line : ptree) {
        Vector2 wp = lp - Vector2(lwidth[li], 0) * justification;
        for (auto& word : line) {
            if (borderColor) {
                Color bc = borderColor.get() * Color(1, 1, 1, 0.5f);
                sftd_draw_text(sfont, wp.x, wp.y-1, bc, size, word.c_str());
                sftd_draw_text(sfont, wp.x, wp.y+1, bc, size, word.c_str());
                sftd_draw_text(sfont, wp.x+1, wp.y, bc, size, word.c_str());
                sftd_draw_text(sfont, wp.x-1, wp.y, bc, size, word.c_str());
            }
            //sftd_draw_text(sfont, wp.x, wp.y, color, size, word.c_str());
            wp.x += spaceWidth + sftd_get_text_width(sfont, size, word.c_str());
        }
        lp += Vector2(0, lineHeight);
        li++;
    }
}
