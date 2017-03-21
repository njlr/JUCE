include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'juce-core',
  header_namespace = 'juce_core',
  exported_headers = subdir_glob([
    ('modules/juce_core', '**/*.hpp'),
    ('modules/juce_core', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_core', '**/*.cpp'),
    ('modules/juce_core', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_core/juce_core.mm']),
    ('^macos.*', ['modules/juce_core/juce_core.mm']),
    ('^linux.*', ['modules/juce_core/juce_core.cpp']),
    ('^windows.*', ['modules/juce_core/juce_core.cpp']),
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
