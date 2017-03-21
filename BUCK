include_defs('//BUCKAROO_DEPS')

macos_linker_flags = [
  '-framework', 'OpenGL',
]

ios_linker_flags = [
  '-framework', 'OpenGLES',
]

linux_linker_flags = [
  '-lGL',
]

mingw_linker_flags = [
  '-lopengl32',
]

cxx_library(
  name = 'juce-opengl',
  header_namespace = 'juce_opengl',
  exported_headers = subdir_glob([
    ('modules/juce_opengl', '**/*.hpp'),
    ('modules/juce_opengl', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_opengl', '**/*.cpp'),
    ('modules/juce_opengl', '**/*.mm'),
  ]),
  platform_srcs = [
    ('default', ['modules/juce_opengl/juce_opengl.mm']),
    ('^macos.*', ['modules/juce_opengl/juce_opengl.mm']),
    ('^linux.*', ['modules/juce_opengl/juce_opengl.cpp']),
    ('^windows.*', ['modules/juce_opengl/juce_opengl.cpp']),
    ('^ios.*', ['modules/juce_opengl/juce_opengl.mm']),
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
    ('^linux.*', linux_linker_flags),
    ('^windows.*', []),
    ('^mingw.*', mingw_linker_flags),
  ],
  visibility = [
    'PUBLIC',
  ],
  deps = BUCKAROO_DEPS,
)
