import os
import subprocess
import sys

# Define paths
project_root = os.getcwd()  # Current directory
build_dir = os.path.join(project_root, "build")
bin_dir = os.path.join(project_root, "bin")

# Step 1: Create directories if they don't exist
os.makedirs(build_dir, exist_ok=True)
os.makedirs(bin_dir, exist_ok=True)

# Step 2: Change to the build directory
os.chdir(build_dir)

# Step 3: Run CMake to generate build files
cmake_command = ['cmake', '-G', 'Unix Makefiles', '..']
if sys.platform.startswith("win"):
    cmake_command = ['cmake', '-G', 'MinGW Makefiles', '..']  # Windows alternative

subprocess.run(cmake_command, check=True)

# Step 4: Run the build command (make or mingw32-make)
build_command = ['make']
if sys.platform.startswith("win"):
    build_command = ['mingw32-make']

subprocess.run(build_command, check=True)

# Step 5: Find the executable (assuming the CMakeLists.txt target name is "my_project")
executable_path = os.path.join(build_dir, "teste")

# If on Windows, add .exe extension
if sys.platform.startswith("win"):
    executable_path += ".exe"

# Ensure the executable exists before running
if not os.path.exists(executable_path):
    print(f"Error: Executable not found at {executable_path}")
    sys.exit(1)

# Step 6: Run the compiled executable
print("Running the program...")
subprocess.run([executable_path])
