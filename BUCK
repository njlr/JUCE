include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'juce-data-structures',
  header_namespace = 'juce_data_structures',
  exported_headers = subdir_glob([
    ('modules/juce_data_structures', '**/*.hpp'),
    ('modules/juce_data_structures', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_data_structures', '**/*.cpp'),
    ('modules/juce_data_structures', '**/*.mm'),
  ]),
  srcs = [
    'modules/juce_data_structures/juce_data_structures.cpp',
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
