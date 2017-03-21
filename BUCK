include_defs('//BUCKAROO_DEPS')

macos_linker_flags = [
  '-framework', 'Accelerate',
]

cxx_library(
  name = 'juce-audio-basics',
  header_namespace = 'juce_audio_basics',
  exported_headers = subdir_glob([
    ('modules/juce_audio_basics', '**/*.hpp'),
    ('modules/juce_audio_basics', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_audio_basics', '**/*.cpp'),
    ('modules/juce_audio_basics', '**/*.mm'),
  ]),
  srcs = [
    'modules/juce_audio_basics/juce_audio_basics.cpp',
  ],
  compiler_flags = [
    '-std=c++14',
    '-DNDEBUG',
    '-DJUCE_STANDALONE_APPLICATION',
    '-DJUCE_GLOBAL_MODULE_SETTINGS_INCLUDED',
  ],
  platform_linker_flags = [
    ('defualt', macos_linker_flags),
    ('^ios.*', macos_linker_flags),
    ('^macos.*', macos_linker_flags),
    ('^linux.*', []),
    ('^windows.*', []),
  ],
  visibility = [
    'PUBLIC',
  ],
  deps = BUCKAROO_DEPS,
)
