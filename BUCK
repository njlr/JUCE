include_defs('//BUCKAROO_DEPS')

ios_linker_flags = [
  '-framework', 'UIKit',
]

macos_linker_flags = [
  '-framework', 'Cocoa',
  '-framework', 'Carbon',
  '-framework', 'QuartzCore',
]

linux_linker_flags = [
  '-lx11',
  '-lxinerama',
  '-lxext',
]

cxx_library(
  name = 'juce-gui-basics',
  header_namespace = 'juce_gui_basics',
  exported_headers = subdir_glob([
    ('modules/juce_gui_basics', '**/*.hpp'),
    ('modules/juce_gui_basics', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_gui_basics', '**/*.cpp'),
    ('modules/juce_gui_basics', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_gui_basics/juce_gui_basics.mm']),
    ('^macos.*', ['modules/juce_gui_basics/juce_gui_basics.mm']),
    ('^linux.*', ['modules/juce_gui_basics/juce_gui_basics.cpp']),
    ('^windows.*', ['modules/juce_gui_basics/juce_gui_basics.cpp']),
    ('^ios.*', ['modules/juce_gui_basics/juce_gui_basics.mm']),
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
    ('^ios.*', ios_linker_flags),
  ],
  visibility = [
    'PUBLIC',
  ],
  deps = BUCKAROO_DEPS,
)
