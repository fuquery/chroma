import os
from pathlib import Path
import sys
import lit.formats

config.name = "chroma-test"

repo_root = Path(__file__).parent
config.test_source_root = repo_root / "test"
config.test_exec_root   = repo_root / "build"
config.suffixes = [".cpp"]
config.test_format = lit.formats.ShTest(execute_external=True)


include_path = f"-I{Path(__file__).parent / 'include'}"
clang_flags = f"-std=c++26 -freflection-latest {include_path}"
gcc_flags   = f"-std=c++26 -freflection {include_path}"

replacements = {
    "STATIC_ASSERT": r"CHECK: error: static assertion failed{{.*}}",
    "ERROR_HERE": r"CHECK: NEXT_LINE error",
    "ERROR": r"CHECK: error",
    "NEXT_LINE": r"{{.*}}:[[@LINE+1]]:{{[0-9]+}}:",
}

def sed_escape(s: str) -> str:
    # escape for sed replacement (delimiter |)
    return s.replace("\\", r"\\").replace("|", r"\|").replace("&", r"\&")

parts = []
for k, v in replacements.items():
    parts.append(f"-e 's|{k}|{sed_escape(v)}|g'")
diag_replacements = "sed " + " ".join(parts)


compiler = lit_config.params.get("compiler")
if compiler == "clang":
  config.available_features.add("clang")
  config.substitutions.append(("%verify", f"not clang++ {clang_flags} -c %s 2>&1 | FileCheck <({diag_replacements} %s)"))
  config.substitutions.append(("%compile", f"clang++ {clang_flags} -c %s 2>&1"))
elif compiler == "gcc":
  config.available_features.add("gcc")
  config.substitutions.append(("%verify", f"not g++ {gcc_flags} -c %s 2>&1 | FileCheck <({diag_replacements} %s)"))
  config.substitutions.append(("%compile", f"g++ {gcc_flags} -c %s 2>&1"))
else:
  print(f"Invalid compiler. Select a compiler with -Dcompiler={{gcc,clang}}")
  sys.exit(1)
