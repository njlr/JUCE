include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'juce-blocks-basics',
  header_namespace = 'juce_blocks_basics',
  exported_headers = subdir_glob([
    ('modules/juce_blocks_basics', '**/*.hpp'),
    ('modules/juce_blocks_basics', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_blocks_basics', '**/*.cpp'),
    ('modules/juce_blocks_basics', '**/*.mm'),
  ]),
  srcs = [
    'modules/juce_blocks_basics/juce_blocks_basics.cpp',
  ],
  compiler_flags = [
    '-std=c++14',
    '-DNDEBUG',
    '-DJUCE_STANDALONE_APPLICATION',
    '-DJUCE_GLOBAL_MODULE_SETTINGS_INCLUDED',
  ],
  visibility = [
    'PUBLIC',
  ],
  deps = BUCKAROO_DEPS,
)
