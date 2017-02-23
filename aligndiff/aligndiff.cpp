// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "aligndiff.h"
#include <cassert>

namespace aligndiff {

DiffEdit makeDiffEdit(char character, DiffOperation operation)
{
    DiffEdit edit;
    edit.character = character;
    edit.operation = operation;
    return edit;
}

void sortDiffEdits(std::vector<DiffEdit> & edits)
{
    for (size_t k = 0; k < edits.size(); ++k) {
        bool swapped = false;
        for (size_t i = 1 + (k % 2); i < edits.size(); i += 2) {
            auto & a = edits[i - 1];
            auto & b = edits[i];
            if ((a.operation == DiffOperation::Insertion) && (b.operation == DiffOperation::Deletion)) {
                std::swap(a, b);
                swapped = true;
            }
            else if ((a.character == b.character) && (a.operation < b.operation)) {
                static_assert(DiffOperation::Deletion < DiffOperation::Equality, "");
                static_assert(DiffOperation::Equality < DiffOperation::Insertion, "");
                std::swap(a, b);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

std::vector<DiffHunk> convertToDiffHunk(const std::vector<DiffEdit>& edits)
{
    std::vector<DiffHunk> hunks;
    for (const auto& edit : edits) {
        if (hunks.empty() || (hunks.back().operation != edit.operation)) {
            DiffHunk hunk;
            hunk.text = edit.character;
            hunk.operation = edit.operation;
            hunks.push_back(std::move(hunk));
        }
        else {
            assert(hunks.back().operation == edit.operation);
            hunks.back().text += edit.character;
        }
    }
    return hunks;
}

std::string convertToLCS(const std::vector<DiffEdit>& edits)
{
    std::string lcs;
    for (const auto& edit : edits) {
        if (edit.operation == DiffOperation::Equality) {
            lcs += edit.character;
        }
    }
    return lcs;
}

} // namespace aligndiff
