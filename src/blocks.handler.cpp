#include "blocks.handler.hpp"

#include "utils.hpp"
#include "../main.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

// Treat some data to make a block.
void process_block
(
    const std::string &block,
    std::vector<SubtitlesBlock> &output
)
{
    if (block.empty())
    {
        return;
    }

    std::istringstream block_data(block);
    std::string index, timestamp, subtitle, content;

    // We need to have at least two lines to try to read the text.
    if (std::getline(block_data, index) && std::getline(block_data, timestamp))
    {
        // Read what's remaining.
        while (std::getline(block_data, content))
        {
            subtitle += content + "\n";
        }

        if (!subtitle.empty() && is_an_integer(index))
        {
            output.push_back({ std::stoi(index), timestamp, subtitle }); // Register the block.
        }
    }
}

// Load a subtitle file into a list of blocks.
std::vector<SubtitlesBlock> load_subtitles_file_data
(
    std::stringstream &file_content
)
{
    std::cout << "Loading subtitle blocks..\n";

    std::vector<SubtitlesBlock> output;
    std::string line, block;

    while (std::getline(file_content, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            // Remove any "\r" as it looks like an empty line visually, but actually isn't for the machine.
            line.pop_back();
        }

        if (trim(line).empty())
        {
            // Try to treat all of the collected data so far as a block, if we finally reached an empty line.
            process_block(block, output);
            block.clear();
        }
        else block += line + "\n"; // Add the line to the block we are currently loading.
    }

    process_block(block, output); // Process the last block.
    std::cout << output.size() << " blocks loaded successfully!\n";
    return output;
}

// Return true if a block is empty.
bool remove_block_if_empty
(
    const SubtitlesBlock &block
)
{
    const std::string subtitles_text = trim(block.text);
    return subtitles_text.empty() ? true : false;
}
