{
  'conditions': [
    ['OS=="linux"', {
      'variables' : {
        # Find the pull path to the pg_config command, since iy may not be on the PATH
        'pgconfig': '<!(which pg_config || find /usr/bin /usr/local/bin /usr/pg* /opt -executable -name pg_config -print -quit)'
      }
    }, {
      #Default to assuming pg_config is on the PATH.
      'variables': {
        'pgconfig': 'pg_config'
      },
    }]
  ],
  'targets': [
    {
      'target_name': 'libpq-bare-native',
      'sources': [
        'src/libpq_bare.cc',
      ],
      'include_dirs': [
        '<!@(<(pgconfig) --includedir)',
        '<!@(node -p "require(\'node-addon-api\').include")'
      ],
      'dependencies': ['<!(node -p "require(\'node-addon-api\').gyp")'],
      'conditions' : [
        ['OS=="linux"', {
            'cflags': ['-fvisibility=hidden', '-fno-exceptions']
        }],
        ['OS=="win"', {
          'libraries' : ['ws2_32.lib','secur32.lib','crypt32.lib','wsock32.lib','msvcrt.lib','libpq.lib'],
          'msvs_settings': {
            'VCLinkerTool' : {
              'AdditionalLibraryDirectories' : [
                '<!@(<(pgconfig) --libdir)\\'
              ]
            },
          }
        }, { # OS!="win"
          'libraries' : ['-lpq -L<!@(<(pgconfig) --libdir)'],
          'ldflags' : ['<!@(<(pgconfig) --ldflags)']
        }],
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7'
          }
        }]
      ]
    }
  ]
}
