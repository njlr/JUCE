include_defs('//BUCKAROO_DEPS')

macos_linker_flags = [
  '-frameworks', 'CoreAudio',
  '-frameworks', 'CoreMIDI',
  '-frameworks', 'AudioToolbox',
]

ios_linker_flags = [
  '-frameworks', 'AudioToolbox',
]

cxx_library(
  name = 'juce-audio-processors',
  header_namespace = 'juce_audio_processors',
  exported_headers = subdir_glob([
    ('modules/juce_audio_processors', '**/*.hpp'),
    ('modules/juce_audio_processors', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_audio_processors', '**/*.cpp'),
    ('modules/juce_audio_processors', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_audio_processors/juce_audio_processors.mm']),
    ('^macos.*', ['modules/juce_audio_processors/juce_audio_processors.mm']),
    ('^linux.*', ['modules/juce_audio_processors/juce_audio_processors.cpp']),
    ('^windows.*', ['modules/juce_audio_processors/juce_audio_processors.cpp']),
    ('^ios.*', ['modules/juce_audio_processors/juce_audio_processors.mm']),
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
    ('^ios.*', ios_linker_flags),
  ],
  visibility = [
    'PUBLIC',
  ],
  deps = BUCKAROO_DEPS,
)
