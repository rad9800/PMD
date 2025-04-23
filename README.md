# Practical Malware Development

## Exercise 1 - Environment Setup

1. Get a Windows virtual machine setup within a hypervisor.
   a. Make sure to take a snapshot of your base installation.
2. Download and install Visual Studio 2022 - https://visualstudio.microsoft.com/vs/
   a. Select `Desktop development with C++` workload when installing
3. Download and install:
   - DebugView++ - https://github.com/CobaltFusion/DebugViewPP
   - PE Bear - https://github.com/hasherezade/pe-bear
   - ProcMon - https://learn.microsoft.com/en-us/sysinternals/downloads/procmon
   - Ghidra - https://www.ghidra-sre.org/
   - Everything - https://www.voidtools.com/

Additionally (optional), for a fuller reversing experience, setup symbols:

`setx _NT_SYMBOL_PATH c:\Symbols;srv*c:\Symbols*https://msdl.microsoft.com/download/symbols`

`mkdir \symbols`

4. Open `PMD.sln` within Visual Studio.
5. Select the `setup` project, and ensure you can:

   a. Compile the project

   b. View the debug print statement within DebugView++.

## Exercise 2 - Understanding PE Properties

1. Update the `template` project compiler and linker flags to manipulate the IAT entries and other PE properties.

   a. Get comfortable with dynamic API resolution and MSDN docs.

   b. Are there any other properties that stand out? If you run Strings.exe against the binary, do any strings stand out?

   c. Can you remove/update them?

Use any tooling of your choice to complete the exercise (e.g. dumpbin/PE Bear). A wrapper around pefile has been provided under `scripts\props.py` (make sure to install the reqs).

2. Download some malware samples from [VXUG](https://vx-underground.org/)

   a. What are the main differences between benign and malicious executables?

   b. What are the main differences between our binary and benign executables?

### Further Resources

- https://learn.microsoft.com/en-us/cpp/build/reference/dumpbin-reference?view=msvc-170
- https://learn.microsoft.com/en-us/windows/win32/debug/pe-format
- https://learn.microsoft.com/en-us/previous-versions/ms809762(v=msdn.10)
- https://cloud.google.com/blog/topics/threat-intelligence/tracking-malware-import-hashing/
- https://github.com/rad9800/misc/blob/main/generic/fix-entropy.cpp
- https://github.com/rad9800/misc/blob/main/generic/stack-strings.cpp

## Exercise 3 - Compile Time API Hashing

The current API hashing algorithm used is fnv1a.

1. Open the `solution` project and call MessageBoxA using the API hashing framework.
2. Use a different hashing algorithm and ensure you can still call MessageBoxA.

### Further Resources

- https://github.com/vxunderground/VX-API/tree/main/VX-API
- https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messageboxa

## Exercise 4 - Find and Leverage DLL Hijacking

1. Download Cisco Webex (https://www.webex.com/downloads.html)
2. Find CiscoCollabHost and see what DLLs get loaded

   - Use Procmon/PE Bear/Ghidra or whatever!

3. Open CiscoCollabHost in Ghidra and identify different ways to get code execution from sideloading

4. Edit the `dll_template` to sideload your target binary. Verify you can see the debug string in DebugView++.

5. Update the `LastWriteTime` and `CreationTime` of `dll_template.dll` to match the target DLL.

### Further Resources

- https://hijacklibs.net/
- https://github.com/sadreck/Spartacus

## Exercise 5 - Shellcode Execution

1. Compile and run the utility project.

   a. Additionally, consider running it on your host system.

2. Copy the identified DLL to the `x64/{Debug,Release}` directory and update the loader code.
3. Update `execute_sc` to execute your shellcode with a different function with the API hashing framework.

### Further Resources

- https://github.com/Wra7h/FlavorTown

## Exercise 6 - Putting it Together

1. Create a new DLL project and put together:
   a. DLL Sideloading
   b. Shellcode Execution from Sideload
2. Verify your PE properties are as expected.
3. Compile your payload in Release and package in a format suitable for delivery.

## Exercise 7 - Payload Hosting

1. Sign up for a cloud storage provider (e.g. AWS/CloudFlare)
2. Package your payload and upload it

   a. Additionally, investigate ways to limit/audit download access

3. Take a snapshot of your VM
4. Revert to the base VM and play your full "delivery" scenario

   - e.g. navigating a user to the URL and getting them to download. Ensure it works.

## Exercise 8 - Building Payloads with Github Actions

1. Create a Git repository with the contents of this project
2. Validate that you can run the Action and the artifacts work
3. Update `.github\workflows\build.yml` to do additional pre/post processing as you want that saves time. Here are some ideas:
   - Run `props.py` and validate/include the output
   - Automate payload packaging in Python
   - Automate the updating of `LastWriteTime` and `CreationTime` to match a target
