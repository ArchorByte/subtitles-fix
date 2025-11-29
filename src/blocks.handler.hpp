#include "../main.hpp"

#include <vector>
#include <sstream>

#ifndef BLOCKS_HANDLER_HPP
#define BLOCKS_HANDLER_HPP

std::vector<SubtitlesBlock> load_subtitles_file_data
(
    std::stringstream &file_content
);

bool remove_block_if_empty
(
    const SubtitlesBlock &block
);

#endif
