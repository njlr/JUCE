include_defs('//BUCKAROO_DEPS')

macos_linker_flags = [
  '-framework', 'CoreAudio',
  '-framework', 'CoreMIDI',
  '-framework', 'QuartzCore',
  '-framework', 'AudioToolbox',
]

ios_linker_flags = [
  '-framework', 'QuartzCore',
  '-framework', 'AudioToolbox',
]

linux_linker_flags = [
  '-lalsa',
]

mingw_linker_flags = [
  '-lwinmm',
]

cxx_library(
  name = 'juce-audio-formats',
  header_namespace = 'juce_audio_formats',
  exported_headers = subdir_glob([
    ('modules/juce_audio_formats', '**/*.hpp'),
    ('modules/juce_audio_formats', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_audio_formats', '**/*.cpp'),
    ('modules/juce_audio_formats', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_audio_formats/juce_audio_formats.mm']),
    ('^macos.*', ['modules/juce_audio_formats/juce_audio_formats.mm']),
    ('^linux.*', ['modules/juce_audio_formats/juce_audio_formats.cpp']),
    ('^windows.*', ['modules/juce_audio_formats/juce_audio_formats.cpp']),
    ('^ios.*', ['modules/juce_audio_formats/juce_audio_formats.mm']),
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
    ('^linux.*', linux_linker_flags),
    ('^windows.*', []),
    ('^mingw.*', mingw_linker_flags),
    ('^ios.*', ios_linker_flags),
  ],
  visibility = [
    'PUBLIC',
  ],
  deps = BUCKAROO_DEPS,
)
