include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'juce-cryptography',
  header_namespace = 'juce_cryptography',
  exported_headers = subdir_glob([
    ('modules/juce_cryptography', '**/*.hpp'),
    ('modules/juce_cryptography', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_cryptography', '**/*.cpp'),
    ('modules/juce_cryptography', '**/*.mm'),
  ]),
  srcs = [
    'modules/juce_cryptography/juce_cryptography.cpp',
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
