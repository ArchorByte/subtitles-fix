#include "cues.remover.hpp"

#include "../main.hpp"

#include <regex>
#include <string>
#include <iostream>

// Remove the cues (ex: (CUE) or [CUE]) from a subtitle block.
void remove_cues
(
    SubtitlesBlock &block
)
{
    const std::string subtitles_text = block.text;

    // Try to remove anything that is within () or [].
    block.text = std::regex_replace(block.text, std::regex(R"(\([^)]*\))"), "");
    block.text = std::regex_replace(block.text, std::regex(R"(\[[^\]]*\])"), "");

    if (subtitles_text != block.text)
    {
        std::cout << "Removed cues from block #" << block.index << "!\n";
    }
}
