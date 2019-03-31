tidy:
	find lib -name "*.cpp" | xargs -l -I % clang-tidy % -checks=clang-analyzer-*,bugprone-*,modernize-*,performance-*,readability-*,misc-* -- -std=c++1z -Iinclude/
