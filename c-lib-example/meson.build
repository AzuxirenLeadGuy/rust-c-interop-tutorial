project(
  'sample_clib',
  'c',
  meson_version : '>= 1.3.0',
  version : '1.0',
  default_options : ['warning_level=3'],
)

sources = [
  'src/sample_clib.c',
]

include_dir = include_directories('include')

sample_clib = both_libraries(
	'sample_clib',
	sources,
	install : true,
	include_directories: include_dir,
	c_shared_args: ['-DLIBTYPE=2'],
	c_static_args: ['-DLIBTYPE=1'],
)

install_headers('include/sample_clib.h')

unit_test_ex = executable(
	'sample_clib_test',
	'test/test.c',
	install : false,
	include_directories: include_dir,
	link_with: sample_clib,
)

test('sample_clib_test run', unit_test_ex)
