project('hello', 'c')
incdir = include_directories('include')
cc = meson.get_compiler('c')
sources = ['main.c', 'changepoint.c']
etest = executable('detect', sources,dependencies: [cc.find_library('m')],include_directories : incdir)
test('This is a test',etest)