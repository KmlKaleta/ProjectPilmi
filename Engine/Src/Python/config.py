import os
import sys
import clang.cindex

def init_libclang():
    current_dir = os.path.dirname(os.path.abspath(__file__))
    local_llvm_path = os.path.join(current_dir, "bin", "win64")

    if os.path.exists(os.path.join(local_llvm_path, "libclang.dll")):
        clang.cindex.Config.set_library_path(local_llvm_path)
    else:
        print(f"libclang.dll has not be find inside {local_llvm_path}")
        sys.exit(1)