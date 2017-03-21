include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'juce-box2d',
  header_namespace = '',
  exported_headers = subdir_glob([
    ('modules/juce_box2d', '**/*.hpp'),
    ('modules/juce_box2d', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_box2d', '**/*.cpp'),
    ('modules/juce_box2d', '**/*.mm'),
  ]),
  srcs = [
    'modules/juce_box2d/juce_box2d.cpp',
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
