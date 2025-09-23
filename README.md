<<<<<<< HEAD
<<<<<<< HEAD
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

What is LD_LIBRARY_PATH?

LD_LIBRARY_PATH is an environment variable used on Unix-like systems (Linux, macOS) to specify a list of directories where the dynamic loader (ld.so) should look for shared libraries before the system’s standard library directories (like /lib and /usr/lib).

Why it was necessary to set

When you build and run a program against custom or non-standard shared libraries (for example, your own libfoo.so built in your project directory), those libraries are not installed in the system's default search paths. By setting LD_LIBRARY_PATH to include the directory containing your library, you instruct the dynamic loader to search that directory so it can locate and load your custom .so at runtime.
=======
Compare the Makefile from Part 2 and Part 3. What are the key differences in the variables and rules that enable the creation of a static library?
Key variable differences

AR / ARFLAGS: Part 3 introduces AR (the archive tool, usually ar) and ARFLAGS (commonly rcs or similar) to control how the static archive is created. Part 2 does not need these if it only links objects directly into an executable.

LIBNAME / LIBTARGET / LIBDIR / PREFIX: Part 3 usually adds variables naming the static library (e.g., LIBNAME = libfoo.a or LIBTARGET = $(BUILD_DIR)/libfoo.a) and possibly LIBDIR or PREFIX for installing the library. Part 2 often only has TARGET for an executable.

LIBOBJS / OBJECTS separation: In Part 3 the objects that form the library are often grouped into LIBOBJS, while the client executable objects remain in OBJECTS. This separation clarifies which objects go into the .a archive vs which are linked into the client.

RANLIB (optional): Part 3 frequently introduces RANLIB as a variable used after ar to index the archive; Part 2 does not use this.

Key rule differences

Rule to build the archive: Part 3 adds an explicit rule such as:

$(LIBTARGET): $(LIBOBJS)
  $(AR) $(ARFLAGS) $@ $(LIBOBJS)
  $(RANLIB) $@

This rule packages object files into a single .a file and indexes it.

Dependency of the client on the archive: The client target in Part 3 depends on the static library file (e.g., client_static: main.o $(LIBTARGET)), which ensures the library is built before linking the client.

Install/uninstall or archive-specific targets: Part 3 may include install or clean_lib rules, and sometimes pattern rules for building object files that are used both by the library and by any clients.

Link command change: In Part 2, the link line might be $(CC) -o $(TARGET) $(OBJECTS) $(LDLIBS), while in Part 3 the static client link line explicitly lists the archive: $(CC) -o client_static main.o $(LIBTARGET) $(LDFLAGS) or uses -L/-l flags to find libraries.

Effect on build workflow

Part 3’s Makefile modularizes the project: you can build and test the library independently; multiple clients can link the same static library; the build rule makes dependencies explicit and reduces duplication.

5) What is the purpose of the ar command? Why is ranlib often used immediately after it?
Purpose of ar

ar (archive) is a Unix utility used to create, modify, and extract from static library archives—collections of object files bundled into a single file, usually with the extension .a. The typical usage when building a static library is:

ar rcs libfoo.a foo1.o foo2.o foo3.o

This command inserts (r) object files into the archive and creates or replaces the archive, with c creating the archive if necessary and s writing an index (on some ar implementations).

The static archive allows the linker to treat a group of object files as a single input: when linking an executable, the linker can pull only those object files from the archive that satisfy currently unresolved symbols.

Why ranlib is used

ranlib generates (or updates) an index (symbol table) for the archive, stored inside the .a file. This index speeds up and enables proper symbol lookup by the linker when it searches the archive for needed symbols.

Historically, some ar implementations did not create the index automatically; ranlib was required to create the symbol table. Modern GNU ar with the s flag (ar rcs) will write the index itself, but projects still often run ranlib for portability and to ensure the archive is always properly indexed on systems where ar doesn't set the symbol table automatically.

3) When you run nm on your client_static executable, are the symbols for functions like mystrlen present? What does this tell you about how static linking works?
What nm shows and why

If you run nm client_static (or nm -C client_static to demangle C++ names), you will typically see symbol entries for functions that were linked into the executable, including functions that originated from static libraries (e.g., mystrlen) — provided the binary has not been stripped.

What this implies about static linking:

Object code is copied into the executable: Static linking copies the machine code for required functions from the library’s object files into the final executable. That’s why nm can list those symbols — they exist inside the binary.

Only needed archive members are included: When linking against a static archive (.a), the linker does not blindly copy every object from the archive. It only extracts the object files that satisfy undefined references in the executable or in previously included objects. So if mystrlen is used by the program, the archive member that defines mystrlen will be pulled in; unused objects remain out of the executable.

Symbols may be local or global and can be stripped: The visibility (local vs global) of the symbol in the resulting binary depends on how it was compiled and linked. Also, running strip or building with -s will remove symbol names, so nm output would then be sparse. Tools like objdump -t or readelf can show symbol tables as well.
>>>>>>> static-build
=======
# BSDSF23M026-OS-A01
1) Explain the linking rule in this part's Makefile: $(TARGET): $(OBJECTS)
What this rule means

$(TARGET): $(OBJECTS) declares that the make target (commonly an executable stored in the $(TARGET) variable) depends on the object files listed in $(OBJECTS). In plain terms:

If any file in $(OBJECTS) is newer than $(TARGET), make will run the commands (the recipe) attached to this rule to rebuild $(TARGET).

The typical recipe for such a rule invokes the compiler or linker to combine object files into an executable. 

2) What is a git tag and why is it useful in a project? What is the difference between a simple tag and an annotated tag?
What is a git tag?

A Git tag is a named pointer to a specific commit. Tags are typically used to mark important points in history such as version releases (e.g., v1.0.0, v2.1.3-rc1). Unlike branches, tags are generally static references that indicate, "this commit corresponds to release X." Tags provide an easy and human-readable way to find the exact commit used for a release, debug builds, or other milestones.


3) What is the purpose of creating a "Release" on GitHub? What is the significance of attaching binaries (like your client executable) to it?
Purpose of a GitHub Release

A GitHub "Release" is a higher-level construct associated with a Git tag that packages release notes, changelogs, and optional binary artifacts in one place. Its main purposes:

Distribution point: Releases provide a single, discoverable place where users can download official project snapshots and binaries.

Release notes & changelogs: Releases allow maintainers to publish human-readable notes describing what changed, migration steps, important fixes, or known issues.

CI/CD integration: Many CI pipelines are set up to create a tag and then automatically publish a Release with generated artifacts.

Visibility & discoverability: Releases are surfaced on the repository page.
>>>>>>> multifile-build
