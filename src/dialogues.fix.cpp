#include "dialogues.fix.hpp"

#include "utils.hpp"
#include "../main.hpp"

#include <regex>
#include <string>
#include <sstream>
#include <iostream>

// "Fix" dialogues.
// We remove dashes that are alone or whitespaces between dashes and text.
void fix_dialogues
(
    SubtitlesBlock &block
)
{
    std::stringstream block_data(block.text);
    std::string output, line;

    bool modified = false;
    int dash_count = 0;

    while (std::getline(block_data, line))
    {
        std::string trimmed_line = trim(line);

        // Check if there is any dash at the beginning of the line.
        if (trimmed_line.rfind("-", 0) == 0)
        {
            dash_count++;
        }

        // Line with only a dash in it.
        if (trimmed_line == "-")
        {
            continue;
        }

        // Remove any whitespace between a dash and the rest of the text.
        if (trimmed_line.rfind("- ", 0) == 0)
        {
            trimmed_line.erase(1, 1);
            modified = true;
        }

        // Preserve all return to line if there still is any content.
        if (!output.empty())
        {
            output += "\n";
        }

        output += trimmed_line;
    }

    if (dash_count == 1)
    {
        std::stringstream output_sstream(output); // Convert the output to sstream.
        std::stringstream updated_output;

        // Find and remove the only starting dash existing to delete it.
        while (std::getline(output_sstream, line))
        {
            if (line.rfind("-", 0) == 0)
            {
                line.erase(0, 1);
                modified = true;
            }

            updated_output << line << "\n";
        }

        // Convert the sstream to string and overwrite the output.
        output = updated_output.str();
    }

    block.text = output;

    if (modified)
    {
        std::cout << "Dialogues fixed for block " << block.index << "!\n";
    }
}
