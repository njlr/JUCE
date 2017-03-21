include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'juce-tracktion-marketplace',
  header_namespace = 'juce_tracktion_marketplace',
  exported_headers = subdir_glob([
    ('modules/juce_tracktion_marketplace', '**/*.hpp'),
    ('modules/juce_tracktion_marketplace', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_tracktion_marketplace', '**/*.cpp'),
    ('modules/juce_tracktion_marketplace', '**/*.mm'),
  ]),
  srcs = [
    'modules/juce_tracktion_marketplace/juce_tracktion_marketplace.cpp',
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
