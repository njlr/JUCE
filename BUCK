include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'juce-graphics',
  header_namespace = '',
  exported_headers = subdir_glob([
    ('modules/juce_graphics', '**/*.hpp'),
    ('modules/juce_graphics', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_graphics', '**/*.cpp'),
    ('modules/juce_graphics', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_graphics/juce_graphics.mm']),
    ('^macos.*', ['modules/juce_graphics/juce_graphics.mm']),
    ('^linux.*', ['modules/juce_graphics/juce_graphics.cpp']),
    ('^windows.*', ['modules/juce_graphics/juce_graphics.cpp']),
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
