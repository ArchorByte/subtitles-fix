#include "main.hpp"

#include "config.hpp"
#include "src/blocks.handler.hpp"
#include "src/cues.remover.hpp"
#include "src/dialogues.fix.hpp"
#include "src/speakers.remover.hpp"
#include "src/utils.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <sstream>

int main()
{
    std::string file_path;
    std::cout << "Path to the subtitle file: ";
    std::getline(std::cin, file_path);

    if (!std::filesystem::exists(file_path))
    {
        std::cerr << "No such file or directory: " << file_path << "!\n";
        return -1;
    }

    if (!std::filesystem::is_regular_file(file_path))
    {
        std::cerr << "This file is not valid!\n";
        return -1;
    }

    std::ifstream subtitles_file(file_path);

    if (!subtitles_file.is_open())
    {
        std::cerr << "Failed to open the subtitles file!\n";
        return -1;
    }

    // Read the file content and put it in an sstream buffer.
    std::stringstream buffer;
    buffer << subtitles_file.rdbuf();

    // Load the subtitle file block by block.
    std::vector<SubtitlesBlock> output = load_subtitles_file_data(buffer);
    subtitles_file.close();

    const int original_block_count = output.size();

    for (int i = 0; i < output.size();)
    {

        SubtitlesBlock &subtitles_block = output[i];

        // Read block's data.
        int block_index = subtitles_block.index;
        const std::string block_timestamp = subtitles_block.timestamp;
        std::string block_subtitles = subtitles_block.text;

        if (block_timestamp.empty())
        {
            // Delete the block if it's not valid.
            output.erase(output.begin() + i);
        }

        if (Config::FIX_INDEXES && (i + 1) != block_index)
        {
            subtitles_block.index = i + 1;
            std::cout << "Fixed a subtitle block index: " << block_index << " -> " << i + 1 << "!\n";
        }

        // Examples of cue: (ACTION) or [ACTION].
        if (Config::REMOVE_CUES)
        {
            remove_cues(subtitles_block);
        }

        if (Config::REMOVE_SPEAKERS)
        {
            remove_speakers(subtitles_block);
        }

        if (Config::FIX_DIALOGUES)
        {
            fix_dialogues(subtitles_block);
        }

        if (Config::DELETE_EMPTY_BLOCKS)
        {
            const bool delete_block = remove_block_if_empty(subtitles_block);

            if (delete_block)
            {
                output.erase(output.begin() + i); // Delete the block from the list.
                std::cout << "Deleted empty block " << (i + 1) << "/" << original_block_count << "!\n";
                continue;
            }
        }

        i++;
    }

    const std::string folder_path = std::filesystem::path(file_path).parent_path().string();
    const std::string file_name = std::filesystem::path(file_path).filename().string();

    // Determine the output path depending on the config file's data.
    const std::string output_file_path = Config::OVERWRITE_ORIGINAL_FILE ? file_path : folder_path + "/fixed." + file_name;
    std::ofstream output_file(output_file_path);

    if (!output_file.is_open())
    {
        std::cerr << "Failed to open the output file!\n";
        return -1;
    }

    // Write all remaining blocks into the output file.
    for (const SubtitlesBlock subtitles_block : output)
    {
        const int block_index = subtitles_block.index;
        const std::string block_timestamp = subtitles_block.timestamp;
        const std::string block_subtitles = subtitles_block.text;

        output_file << block_index << "\n" << block_timestamp << "\n" << block_subtitles << "\n\n";
    }

    output_file.close();
    std::cout << "\nDone! Output file: " << output_file_path << ".\n";
    return 0;
}
