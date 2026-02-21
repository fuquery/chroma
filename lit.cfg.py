import os
from pathlib import Path
import sys
import lit.formats

config.name = "chroma-compile-fail"

repo_root = Path(__file__).parent
config.test_source_root = repo_root / "test"
config.test_exec_root   = repo_root / "build"
config.suffixes = [".cpp"]
config.test_format = lit.formats.ShTest(execute_external=True)


include_path = f"-I{Path(__file__).parent / 'include'}"
clang_flags = f"-std=c++26 -freflection-latest {include_path}"
gcc_flags   = f"-std=c++26 -freflection {include_path}"

filecheck_defines = ""


compiler = lit_config.params.get("compiler")
if compiler == "clang":
  config.available_features.add("clang")
  config.substitutions.append(("%verify", f"not clang++ {clang_flags} %s 2>&1 | FileCheck {filecheck_defines} %s"))
  config.substitutions.append(("%compile", f"clang++ {clang_flags} %s 2>&1"))
elif compiler == "gcc":
  config.available_features.add("gcc")
  config.substitutions.append(("%verify", f"not g++ {gcc_flags} %s 2>&1 | FileCheck {filecheck_defines} %s"))
  config.substitutions.append(("%compile", f"g++ {gcc_flags} %s 2>&1"))
else:
  print(f"Invalid compiler. Select a compiler with -Dcompiler={{gcc,clang}}")
  sys.exit(1)