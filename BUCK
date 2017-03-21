include_defs('//BUCKAROO_DEPS')

macos_linker_flags = [
  '-framework', 'WebKit',
]

cxx_library(
  name = 'juce-gui-extra',
  header_namespace = 'juce_gui_extra',
  exported_headers = subdir_glob([
    ('modules/juce_gui_extra', '**/*.hpp'),
    ('modules/juce_gui_extra', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_gui_extra', '**/*.cpp'),
    ('modules/juce_gui_extra', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_gui_extra/juce_gui_extra.mm']),
    ('^macos.*', ['modules/juce_gui_extra/juce_gui_extra.mm']),
    ('^linux.*', ['modules/juce_gui_extra/juce_gui_extra.cpp']),
    ('^windows.*', ['modules/juce_gui_extra/juce_gui_extra.cpp']),
    ('^ios.*', ['modules/juce_gui_extra/juce_gui_extra.mm']),
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
