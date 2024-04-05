#!/usr/bin/env python3

# Read version number from file
with open('./build-version/version.txt', 'r') as file:
    version_content = file.read().strip()

# Parse version components
version_list = version_content.split('.')
project_version_major = int(version_list[0])
project_version_minor = int(version_list[1])
project_version_patch = int(version_list[2])
project_version_build = int(version_list[3])

# Increment build number
project_version_build += 1
if project_version_build > 100:
    project_version_build = 0
    project_version_minor += 1
    if project_version_minor > 100:
        project_version_minor = 0
        project_version_major += 1

# Write updated version number back to file
with open('./build-version/version.txt', 'w') as file:
    file.write(f"{project_version_major}.{project_version_minor}.{project_version_patch}.{project_version_build}")

with open('version.h', 'w') as file:
    file.write(f"#define PROJECT_VERSION_MAJOR {project_version_major}\n")
    file.write(f"#define PROJECT_VERSION_MINOR {project_version_minor}\n")
    file.write(f"#define PROJECT_VERSION_PATCH {project_version_patch}\n")
    file.write(f"#define PROJECT_VERSION_BUILD {project_version_build}\n")

