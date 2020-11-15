#pragma once
#ifndef HIGHLIGHTER_INTERACE_H
#define HIGHLIGHTER_INTERFACE_H

#include "core/Cutter.h"

struct HighlightRange {
    RVA startAddress;
    RVA endAddress;
    int index;
    QColor color;
    char* toolTip;
};

class HighlighterInterface : public QObject {
    Q_OBJECT

    public:
    ~HighlighterInterface();
    void addHighlight(RVA startAddress, RVA endAddress, QColor color, char* toolTip);
    void addHighlight(RVA startAddress, RVA endAddress, QColor color);
    void removeHighlight(int index);
    void setHighlightStartAddress(int index, RVA startAddress);
    void setHighlightEndAddress(int index, RVA endAddress);
    void setHighlightColor(int index, QColor color);
    void setHighlightToolTip(int index, char* toolTip);

    HighlightRange* getHighlightRangeByAddress(RVA address);
    HighlightRange* getHighlightRangeByIndex(int index);
    int getHighlightRangeIndex(RVA address);

    QList<HighlightRange> getHighlightRanges(RVA startAddress, RVA endAddress);

    public slots:
    virtual void onRangeClicked(HighlightRange &range, QMouseEvent *event)=0;
    virtual void onRangeContextMenu(HighlightRange &range, QContextMenuEvent *event)=0;
    virtual void onRangeXXX(HighlightRange &range, QEvent *event){(void)range; (void)event;};

    signals:
    void highlightsChanged();

    private:
    QList<HighlightRange> highlights;
    void updateIndicies();


};

#endif