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
