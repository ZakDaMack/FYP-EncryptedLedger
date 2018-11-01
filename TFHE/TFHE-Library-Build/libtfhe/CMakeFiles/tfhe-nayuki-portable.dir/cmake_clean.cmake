file(REMOVE_RECURSE
  "libtfhe-nayuki-portable.pdb"
  "libtfhe-nayuki-portable.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/tfhe-nayuki-portable.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
