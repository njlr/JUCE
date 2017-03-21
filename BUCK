include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'juce-osc',
  header_namespace = 'juce_osc',
  exported_headers = subdir_glob([
    ('modules/juce_osc', '**/*.hpp'),
    ('modules/juce_osc', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_osc', '**/*.cpp'),
    ('modules/juce_osc', '**/*.mm'),
  ]),
  srcs = [
    'modules/juce_osc/juce_osc.cpp',
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
