#include "core/Cutter.h"
#include "HighlighterInterface.h"



HighlighterInterface::~HighlighterInterface()
{

}


HighlightRange *HighlighterInterface::getHighlightRangeByAddress(RVA address)
{
    for (HighlightRange range : highlights) {
        if (range.startAddress <= address && range.endAddress >= address) {
            return &highlights[range.index];
        }
    }
    return nullptr;
}

HighlightRange *HighlighterInterface::getHighlightRangeByIndex(int index)
{
    return &highlights[index];
}

int HighlighterInterface::getHighlightRangeIndex(RVA address)
{
    for (HighlightRange range : highlights) {
        if (range.startAddress <= address && range.endAddress >= address) {
            return range.index;
        }
    }
    return 0;
}

QList<HighlightRange> HighlighterInterface::getHighlightRanges(RVA startAddress, RVA endAddress)
{
    QList<HighlightRange> returnRange;
    for (HighlightRange range : HighlighterInterface::highlights) {
        if (range.startAddress >= startAddress && range.endAddress <= endAddress) {
            returnRange.append(range);
        } else if (range.startAddress <= startAddress && range.endAddress <= endAddress) {
            range.startAddress =
                startAddress; 
            returnRange.append(range);
        } else if (range.startAddress >= startAddress && range.endAddress >= endAddress) {
            range.endAddress = endAddress;
            returnRange.append(range);
        }
    }
    return returnRange;
}

void HighlighterInterface::addHighlight(RVA startAddress, RVA endAddress, QColor color,
                                        char *toolTip = nullptr)
{
    HighlightRange range;
    range.startAddress = startAddress;
    range.endAddress = endAddress;
    range.color = color;
    range.toolTip = toolTip;
    range.index = highlights.size();
    highlights.append(range);
    emit highlightsChanged();
}

void HighlighterInterface::addHighlight(RVA startAddress, RVA endAddress, QColor color)
{
    HighlightRange range;
    range.startAddress = startAddress;
    range.endAddress = endAddress;
    range.color = color;
    range.toolTip = nullptr;
    range.index = highlights.size();
    highlights.append(range);
    emit highlightsChanged();
}


void HighlighterInterface::removeHighlight(int index)
{
    highlights.removeAt(index);
    updateIndicies();
    emit highlightsChanged();
}

void HighlighterInterface::setHighlightStartAddress(int index, RVA startAddress)
{
    highlights[index].startAddress = startAddress;
    emit highlightsChanged();
}

void HighlighterInterface::setHighlightEndAddress(int index, RVA endAddress)
{
    highlights[index].endAddress = endAddress;
    emit highlightsChanged();
}

void HighlighterInterface::setHighlightColor(int index, QColor color)
{
    highlights[index].color = color;
    emit highlightsChanged();
}

void HighlighterInterface::setHighlightToolTip(int index, char *toolTip)
{
    highlights[index].toolTip = toolTip;
    emit highlightsChanged();
}

void HighlighterInterface::updateIndicies()
{
    HighlightRange temp;
    for (int i = 0; i < highlights.size(); i++) {
        HighlightRange temp = highlights.at(i);
        temp.index = i;
        highlights.replace(i, temp);
    }
}


