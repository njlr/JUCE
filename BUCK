include_defs('//BUCKAROO_DEPS')

macos_linker_flags = [
  '-framework', 'CoreAudio',
  '-framework', 'CoreMIDI',
  '-framework', 'AudioToolbox',
]

ios_linker_flags = [
  '-framework', 'CoreAudio',
  '-framework', 'CoreMIDI',
  '-framework', 'AudioToolbox',
  '-framework', 'AVFoundation',
]

linux_linker_flags = [
  '-lalsa',
]

mingw_linker_flags = [
  '-lwinmm',
]

cxx_library(
  name = 'juce-audio-devices',
  header_namespace = 'juce_audio_devices',
  exported_headers = subdir_glob([
    ('modules/juce_audio_devices', '**/*.hpp'),
    ('modules/juce_audio_devices', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_audio_devices', '**/*.cpp'),
    ('modules/juce_audio_devices', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_audio_devices/juce_audio_devices.mm']),
    ('^macos.*', ['modules/juce_audio_devices/juce_audio_devices.mm']),
    ('^linux.*', ['modules/juce_audio_devices/juce_audio_devices.cpp']),
    ('^windows.*', ['modules/juce_audio_devices/juce_audio_devices.cpp']),
    ('^ios.*', ['modules/juce_audio_devices/juce_audio_devices.mm']),
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
