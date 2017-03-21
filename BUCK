include_defs('//BUCKAROO_DEPS')

macos_linker_flags = [
  '-framework', 'DiscRecording',
]

ios_linker_flags = [
  '-framework', 'CoreAudioKit',
]

cxx_library(
  name = 'juce-audio-utils',
  header_namespace = 'juce_audio_utils',
  exported_headers = subdir_glob([
    ('modules/juce_audio_utils', '**/*.hpp'),
    ('modules/juce_audio_utils', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_audio_utils', '**/*.cpp'),
    ('modules/juce_audio_utils', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_audio_utils/juce_audio_utils.mm']),
    ('^macos.*', ['modules/juce_audio_utils/juce_audio_utils.mm']),
    ('^linux.*', ['modules/juce_audio_utils/juce_audio_utils.cpp']),
    ('^windows.*', ['modules/juce_audio_utils/juce_audio_utils.cpp']),
    ('^ios.*', ['modules/juce_audio_utils/juce_audio_utils.mm']),
  ],
  compiler_flags = [
    '-std=c++14',
    '-DNDEBUG',
    '-DJUCE_STANDALONE_APPLICATION',
    '-DJUCE_GLOBAL_MODULE_SETTINGS_INCLUDED',
  ],
  platform_linker_flags = [
    ('default', macos_linker_flags),
    ('^ios.*', ios_linker_flags),
    ('^macos.*', macos_linker_flags),
    ('^linux.*', []),
    ('^windows.*', []),
  ],
  visibility = [
    'PUBLIC',
  ],
  deps = BUCKAROO_DEPS,
)
