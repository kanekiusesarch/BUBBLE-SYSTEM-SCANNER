# BUBBLE-SYSTEM-SCANNER

# Bubble SUPER SYSTEM SCANNER v1.1 alpha (also known as syressundore)

Made by kaneki | https://github.com/kanekiusesarch

BubbleScanner is a fun system scanner that detects your OS, CPU, memory, disk, GPU, and prints a fancy ASCII report.

## Supported Platforms
- Linux (tested on Arch/Bubble OS)
- Windows (64-bit, requires Mingw-w64)
- macOS (requires macOS SDK compile it yourself)
- BSD (FreeBSD, OpenBSD, NetBSD compile it yourself)
  
### Linux compiling tut
```bash
g++ bubblescanner.cpp -o bubblescanner
./bubblescanner
```
### MacOS compiling tut 
```bash
xcode-select --install
clang++ bubblescanner.cpp -o bubblescanner
chmod +x bubblescanner   # only if needed
./bubblescanner
```

### Freebsd Openbsd Netbsd compiling tut
```bash
sudo pkg install clang
for netbsd use the command pkgin install clang
then clang++ bubblescanner.cpp -o bubblescanner
chmod +x bubblescanner
./bubblescanner
```
