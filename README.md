# BSDSF23M026-OS-A01



1) What is Position-Independent Code (-fPIC) and why is it a fundamental requirement for creating shared libraries?
Position-Independent Code (PIC)

Position-Independent Code is machine code that can execute correctly regardless of its absolute memory address. When compiled with the -fPIC (Position Independent Code) flag, the compiler generates code that accesses data and functions through relative addressing instead of hardcoding absolute memory addresses.

Why it is required for shared libraries

Shared library loading: Shared libraries (.so files) can be loaded at arbitrary memory addresses by different processes, depending on what regions of memory are already occupied. Without PIC, the library would assume a fixed address, leading to relocation conflicts.

Memory efficiency: With PIC, the same shared library code can be mapped into multiple processes simultaneously without modification. If a library were not compiled as PIC, each process would need its own relocated copy, wasting memory.

Dynamic linking flexibility: PIC allows the dynamic loader (ld.so) to load and link shared libraries at runtime without recompiling or adjusting large parts of the code.

In summary, -fPIC makes code relocatable and sharable, which is fundamental for the dynamic linking model used by modern operating systems.

2) Explain the difference in file size between your static and dynamic clients. Why does this difference exist?
Observed difference

Static client: Much larger file size.

Dynamic client: Much smaller file size.

Why the difference exists

Static linking: In a statically linked executable, all the library code your program depends on is physically copied into the final binary at link time. This includes standard libraries (e.g., libc) and any other linked code. As a result, the binary contains all the code it needs to run, leading to a significantly larger file size.

Dynamic linking: In a dynamically linked executable, the binary only contains references to the external shared libraries (like libc.so). The actual library code is not embedded into the binary; instead, the operating system's dynamic loader brings in the shared libraries at runtime. This means the executable itself is smaller because it contains only symbol references and metadata for linking, not the full code of the libraries.


