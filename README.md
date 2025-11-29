# Subtitles fix
This small tool will enable you to "fix" your subtitle files. <br/>
You can select what will be fixed by the program, directly from the config file `config.hpp`. <br/>
> For Windows devices, verify your compiler path in the **build.bat** script before compilation.

# 📦 Requirements
- CMake.
- GCC/G++ compilers.

# 📥 Installation
1) Download the project. <br/>
2) Compile it. <br/>
3) Enjoy! <br/>

# ⚙️ Configuration
You can configure the program using the `config.hpp` file. <br/>
The default configuration is available at the bottom of this section. <br/>
Here are the different options you have:
- `"REMOVE_CUES"` -> Remove all cues from your subtitles (example: (CUE) or [CUE]).
- `"REMOVE_SPEAKERS"` -> Remove all speakers from your subtitles (example: ~~SPEAKER:~~ text).
- `"FIX_INDEXES"` -> Fix the indexes of the blocks of your subtitles.
- `"FIX_DIALOGUES"` -> Fix dialogue presentation depending on the amount of dashes and whitespaces.
- `"DELETE_EMPTY_BLOCKS"` -> Delete all empty blocks from the subtitles.
- `"OVERWRITE_ORIGINAL_FILE"` -> Overwrite the targeted file.
``` cpp
constexpr const bool REMOVE_CUES = true;
constexpr const bool REMOVE_SPEAKERS = true;
constexpr const bool FIX_INDEXES = true;
constexpr const bool FIX_DIALOGUES = true;
constexpr const bool DELETE_EMPTY_BLOCKS = true;
constexpr const bool OVERWRITE_ORIGINAL_FILE = false;
```

# 🤝 User Agreement
By downloading and/or using this program, you confirm that you are solely responsible for how you use this software. You agree as well that this agreement extends to any prior version of the program, and any new version of the user agreement in any future update, overwrites this one.
