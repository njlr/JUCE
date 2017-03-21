include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'juce-events',
  header_namespace = 'juce_events',
  exported_headers = subdir_glob([
    ('modules/juce_events', '**/*.hpp'),
    ('modules/juce_events', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_events', '**/*.cpp'),
    ('modules/juce_events', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_events/juce_events.mm']),
    ('^macos.*', ['modules/juce_events/juce_events.mm']),
    ('^linux.*', ['modules/juce_events/juce_events.cpp']),
    ('^windows.*', ['modules/juce_events/juce_events.cpp']),
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
