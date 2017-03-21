include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'juce-audio-plugin-client',
  header_namespace = 'juce_audio_plugin_client',
  exported_headers = subdir_glob([
    ('modules/juce_audio_plugin_client', '**/*.hpp'),
    ('modules/juce_audio_plugin_client', '**/*.h'),
  ]),
  headers = subdir_glob([
    ('modules/juce_audio_plugin_client', '**/*.cpp'),
    ('modules/juce_audio_plugin_client', '**/*.mm'),
  ]),
  srcs = [
    'modules/juce_audio_plugin_client/juce_audio_plugin_client.cpp',
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
