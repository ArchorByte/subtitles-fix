#include "speakers.remover.hpp"

#include "../main.hpp"

#include <iostream>
#include <regex>
#include <string>
#include <sstream>

// Remove speakers (ex: "CHARACTER:") from a subtitle block.
void remove_speakers
(
    SubtitlesBlock &block
)
{
    const std::string original_subtitles_text = block.text;
    std::stringstream subtitles_text(original_subtitles_text); // Convert the content into a sstream.

    std::stringstream output;
    std::string line;

    while (std::getline(subtitles_text, line))
    {
        // If the line is a speaker only, we immediately skip it.
        if (std::regex_match(line, std::regex(R"(^\s*[A-Za-z][A-Za-z0-9 ()'\-]*:\s*$)")))
        {
            continue;
        }

        // Otherwise, we remove the speaker from the line and write it in the output sstream.
        line = std::regex_replace(line, std::regex(R"(^\s*[A-Za-z][A-Za-z0-9 ()'\-]*:\s*)"), "");
        output << line << "\n";
    }

    // Convert the sstream into string.
    const std::string new_subtitles_text = output.str();
    block.text = new_subtitles_text;

    if (original_subtitles_text != new_subtitles_text)
    {
        std::cout << "Removed speakers from block #" << block.index << "!\n";
    }
}
