project(
    'genericArduino',
    'c', 
    'cpp',
    default_options : [
        'c_std=c11', 
        'cpp_std=c++17',
        'b_lto=true',
        'b_pgo=generate',
        'b_coverage=false',
    ],
    version:'0.1.0',
    meson_version: '>= 0.54.0',
)

CC = meson.get_compiler('c')

genericArduino_deps = [
    dependency('ArduinoRaspi', required: true, fallback: 'ArduinoRaspi'),
]

incdir = include_directories('src')

sources = [
    'src/SPIAbstraction.cpp',
]

genericArduino = library(
    'genericArduino',
    sources,
    version : meson.project_version(),
    soversion : '0',
    include_directories : incdir,
    dependencies: genericArduino_deps,
    install : true,
)

genericArduino_dep = declare_dependency(
    include_directories : incdir,
    link_with : genericArduino,
    dependencies : genericArduino_deps,
    version: meson.project_version(),
)

install_subdir('include', install_dir : 'include/genericArduino', strip_directory : true)

pkg = import('pkgconfig')
pkg.generate(genericArduino)

meson.override_dependency('genericArduino',genericArduino_dep)
meson.override_dependency('generic-Arduino',genericArduino_dep)

#if not get_option('no-data')
#    install_subdir('data', install_dir : get_option('datadir') / 'libtrainsim')
#endif
