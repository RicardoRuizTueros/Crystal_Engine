import os
import subprocess
import platform

from SetupPython import PythonConfiguration as PythonRequirements

PythonRequirements.Validate()

from SetupPremake import PremakeConfiguration as PremakeRequirements
from SetupVulkan import VulkanConfiguration as VulkanRequirements

# Change from Scripts directory to root
os.chdir('./../')

premakeInstalled = PremakeRequirements.Validate()
VulkanRequirements.Validate()

if premakeInstalled:
    if platform.system() == "Windows":
        print("\nRunning premake...")
        subprocess.call([os.path.abspath("./scripts/windows_generate_project.bat"), "nopause"])

    print("\nSetup completed!")
else:
    print("Crystal Engine requires Premake to generate project files.")