include_defs('//BUCKAROO_DEPS')

macos_linker_flags = [
  '-framework', 'QTKit',
  '-framework', 'QuickTime',
]

cxx_library(
  name = 'juce-video',
  header_namespace = 'juce_video',
  exported_headers = subdir_glob([
    ('modules/juce_video', '**/*.hpp'),
    ('modules/juce_video', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_video', '**/*.cpp'),
    ('modules/juce_video', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_video/juce_video.mm']),
    ('^macos.*', ['modules/juce_video/juce_video.mm']),
    ('^linux.*', ['modules/juce_video/juce_video.cpp']),
    ('^windows.*', ['modules/juce_video/juce_video.cpp']),
    ('^ios.*', ['modules/juce_video/juce_video.mm']),
  ],
  compiler_flags = [
    '-std=c++14',
    '-DNDEBUG',
    '-DJUCE_STANDALONE_APPLICATION',
    '-DJUCE_GLOBAL_MODULE_SETTINGS_INCLUDED',
  ],
  platform_linker_flags = [
    ('default', macos_linker_flags),
    ('^macos.*', macos_linker_flags),
    ('^linux.*', []),
    ('^windows.*', []),
    ('^ios.*', []),
  ],
  visibility = [
    'PUBLIC',
  ],
  deps = BUCKAROO_DEPS,
)
