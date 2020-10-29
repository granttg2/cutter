#ifndef HIGHLIGHTER_INTERACE_H
#define HIGHLIGHTER_INTERFACE_H

#include "HighlightRange.h"

class HighlighterInterface {
    public:
    virtual HighlightRange getHighlightRanges();
}

#endif