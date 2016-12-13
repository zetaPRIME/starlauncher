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

namespace { // helper functions
    std::vector<std::string> split(const std::string& s, char delim) {
        std::stringstream ss(s);
        std::string item;
        std::vector<std::string> tokens;
        while (getline(ss, item, delim)) {
            tokens.push_back(item);
        }
        return tokens;
    }
    
    void m(std::string text, int size) {
        char buf[text.length()+1];
        text.copy(buf, 999);
    }
}

FontSFTD::~FontSFTD() {
    sftd_free_font(sfont);
}

#define err(nth, wat) *((unsigned int*)0x00100000+(nth))=wat;
#define ded(wat) err(0,wat)
Vector2 FontSFTD::Measure(std::string& text, int size, int maxWidth) {
    int w = 0; int h = 0;
    //sftd_calc_bounding_box(&w, &h, this->sfont, size, maxWidth, text.c_str());
    sftd_calc_bounding_box(&w, &h, this->sfont, size, maxWidth, "Q");
    //h = size;
    w = sftd_get_text_width(this->sfont, size, text.c_str());
    
    //if (w == 0) { ded(0xBEEFFACE); }
    return Vector2(w, h);
}

void FontSFTD::Print(Vector2 position, std::string& text, int size, Color color, Vector2 justification) {
    int lineHeight = 0; int spaceWidth = 0;
    sftd_calc_bounding_box(&spaceWidth, &lineHeight, sfont, size, size*2, "Q");
    spaceWidth = sftd_get_text_width(sfont, size, " ");
    
    std::vector<std::list<std::string>> ptree;
    std::vector<int> lwidth;
    {
        std::stringstream ss(text);
        std::string line, word;
        int maxWidth = 300; // temp
        
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
                    cLineLen = -spaceWidth;
                }
                cLineLen += ww;
                cline->push_back(word);
                //
            }
            lwidth.push_back(cLineLen);
            ptree.push_back(std::list<std::string>());
            cline = &ptree.back();
            cLineLen = -spaceWidth;
        }
    }
    
    Vector2 lp = position - Vector2(0, lwidth.size() * lineHeight) * justification;
    lp.x = floor(lp.x); lp.y = floor(lp.y); // normalize across zero-crossings
    int li = 0;
    
    for (auto& line : ptree) {
        Vector2 wp = lp - Vector2(lwidth[li], 0) * justification;
        for (auto& word : line) {
            sftd_draw_text(sfont, wp.x, wp.y, color, size, word.c_str());
            wp.x += spaceWidth + sftd_get_text_width(sfont, size, word.c_str());
        }
        lp += Vector2(0, lineHeight);
        li++;
    }
    
}

void FontSFTD::Print(VRect rect, std::string& text, int size, Color color, Vector2 justification) {
    
}
